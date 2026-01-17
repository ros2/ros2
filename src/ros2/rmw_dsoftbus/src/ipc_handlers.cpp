/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Copyright (c) 2024 ROS2 KaihongOS Port Project
#include <string.h>  /* C memcpy/memset for OHOS SDK compatibility */
#include <stdlib.h>

// Licensed under the Apache License, Version 2.0

#include "rmw_dsoftbus/ipc_server.h"
#include "rmw_dsoftbus/graph_cache.h"
#include "rmw_dsoftbus/discovery_manager.h"
#include "rmw/rmw.h"  // For rmw_get_implementation_identifier

#include <cstring>

/**
 * @file ipc_handlers.cpp
 * @brief IPC request handlers binding to GraphCache and DiscoveryManager
 *
 * Execution flow:
 * 1. librmw client sends REGISTER_* request
 * 2. Handler parses TLV and calls GraphCache::register_*
 * 3. GraphCache updates local state and triggers graph_change
 * 4. Handler calls DiscoveryManager::broadcast_* for cross-device propagation
 * 5. daemon calls IpcServer::notify_graph_changed() to wake subscribed clients
 */

namespace rmw_dsoftbus {

// gcc-linaro compatibility
using ::memcpy;
using ::memset;
using ::memcmp;
namespace ipc {

// Handler function for daemon
std::pair<int32_t, std::vector<uint8_t>>
handle_ipc_request(
    ClientContext& ctx,
    const DiscoveryIpcHeader& hdr,
    const std::vector<uint8_t>& payload)
{
    // Note: No exception handling - OpenHarmony uses -fno-exceptions
    const auto msg_type = static_cast<DiscoveryIpcMsgType>(hdr.msg_type);

        switch (msg_type) {
            // ---- Graph subscription ----
            case DISCOVERY_IPC_MSG_SUBSCRIBE_GRAPH: {
                ctx.subscribed_graph = true;
                return {0, {}};
            }

            case DISCOVERY_IPC_MSG_UNSUBSCRIBE_GRAPH: {
                ctx.subscribed_graph = false;
                return {0, {}};
            }

            // ---- Node registration ----
            case DISCOVERY_IPC_MSG_REGISTER_NODE: {
                auto tlvs = tlv_parse(payload.data(), static_cast<uint32_t>(payload.size()));

                auto* ns_tlv = tlv_find(tlvs, DISCOVERY_TLV_NODE_NAMESPACE);
                auto* name_tlv = tlv_find(tlvs, DISCOVERY_TLV_NODE_NAME);
                auto* enclave_tlv = tlv_find(tlvs, DISCOVERY_TLV_NODE_ENCLAVE);

                if (!ns_tlv || !name_tlv) {
                    return {-EINVAL, {}};
                }

                std::string node_ns = tlv_as_string(*ns_tlv);
                std::string node_name = tlv_as_string(*name_tlv);
                std::string enclave = enclave_tlv ? tlv_as_string(*enclave_tlv) : "";

                // Register with GraphCache (local state)
                GraphCache::instance().register_node(
                    node_name.c_str(),
                    node_ns.c_str(),
                    enclave.empty() ? nullptr : enclave.c_str());

                // Phase 2.5.3: Broadcast to peers via DiscoveryManager
                GraphNodeInfo node_info;
                node_info.node_name = node_name;
                node_info.node_namespace = node_ns;
                node_info.enclave = enclave;
                DiscoveryManager::instance().broadcast_node_added(node_info);

                // Notify IPC clients of graph change
                uint64_t new_version = GraphCache::instance().get_graph_version();
                IpcServer::instance().notify_graph_changed(new_version);

                return {0, {}};
            }

            case DISCOVERY_IPC_MSG_UNREGISTER_NODE: {
                auto tlvs = tlv_parse(payload.data(), static_cast<uint32_t>(payload.size()));

                auto* ns_tlv = tlv_find(tlvs, DISCOVERY_TLV_NODE_NAMESPACE);
                auto* name_tlv = tlv_find(tlvs, DISCOVERY_TLV_NODE_NAME);

                if (!ns_tlv || !name_tlv) {
                    return {-EINVAL, {}};
                }

                std::string node_ns = tlv_as_string(*ns_tlv);
                std::string node_name = tlv_as_string(*name_tlv);

                GraphCache::instance().unregister_node(node_name.c_str(), node_ns.c_str());

                // Phase 2.5.3: Broadcast removal
                std::string node_key = make_node_key(node_ns, node_name);
                DiscoveryManager::instance().broadcast_node_removed(node_key);

                // Notify IPC clients
                uint64_t new_version = GraphCache::instance().get_graph_version();
                IpcServer::instance().notify_graph_changed(new_version);

                return {0, {}};
            }

            // ---- Endpoint registration ----
            case DISCOVERY_IPC_MSG_REGISTER_ENDPOINT: {
                auto tlvs = tlv_parse(payload.data(), static_cast<uint32_t>(payload.size()));

                auto* kind_tlv = tlv_find(tlvs, DISCOVERY_TLV_ENTITY_KIND);
                auto* topic_tlv = tlv_find(tlvs, DISCOVERY_TLV_TOPIC_NAME);
                auto* type_tlv = tlv_find(tlvs, DISCOVERY_TLV_TYPE_NAME);
                auto* gid_tlv = tlv_find(tlvs, DISCOVERY_TLV_GID);
                auto* qos_tlv = tlv_find(tlvs, DISCOVERY_TLV_QOS_PROFILE);
                auto* node_ns_tlv = tlv_find(tlvs, DISCOVERY_TLV_NODE_NAMESPACE);
                auto* node_name_tlv = tlv_find(tlvs, DISCOVERY_TLV_NODE_NAME);

                if (!kind_tlv || !topic_tlv || !type_tlv || !gid_tlv ||
                    !qos_tlv || !node_ns_tlv || !node_name_tlv) {
                    return {-EINVAL, {}};
                }

                auto kind = static_cast<DiscoveryEntityKind>(tlv_as_u32(*kind_tlv));
                std::string topic = tlv_as_string(*topic_tlv);
                std::string type = tlv_as_string(*type_tlv);
                std::string node_ns = tlv_as_string(*node_ns_tlv);
                std::string node_name = tlv_as_string(*node_name_tlv);

                // Extract GID (24 bytes)
                rmw_gid_t gid;
                memset(&gid, 0, sizeof(gid));
                gid.implementation_identifier = rmw_get_implementation_identifier();
                tlv_as_bytes(*gid_tlv, gid.data, 24);

                // Extract QoS profile
                if (qos_tlv->length != sizeof(DiscoveryQosProfile)) {
                    return {-EINVAL, {}};
                }
                DiscoveryQosProfile qos_bin;
                memcpy(&qos_bin, qos_tlv->value, sizeof(qos_bin));

                // Convert to rmw_qos_profile_t
                rmw_qos_profile_t qos{};
                qos.history = static_cast<rmw_qos_history_policy_t>(qos_bin.history);
                qos.depth = qos_bin.depth;
                qos.reliability = static_cast<rmw_qos_reliability_policy_t>(qos_bin.reliability);
                qos.durability = static_cast<rmw_qos_durability_policy_t>(qos_bin.durability);
                qos.deadline.sec = static_cast<uint64_t>(qos_bin.deadline_ns / 1000000000ULL);
                qos.deadline.nsec = static_cast<uint64_t>(qos_bin.deadline_ns % 1000000000ULL);
                qos.lifespan.sec = static_cast<uint64_t>(qos_bin.lifespan_ns / 1000000000ULL);
                qos.lifespan.nsec = static_cast<uint64_t>(qos_bin.lifespan_ns % 1000000000ULL);
                qos.liveliness = static_cast<rmw_qos_liveliness_policy_t>(qos_bin.liveliness);
                qos.liveliness_lease_duration.sec = static_cast<uint64_t>(qos_bin.liveliness_lease_ns / 1000000000ULL);
                qos.liveliness_lease_duration.nsec = static_cast<uint64_t>(qos_bin.liveliness_lease_ns % 1000000000ULL);

                // Build GraphEndpointInfo for broadcast
                GraphEndpointInfo endpoint_info;
                endpoint_info.topic_name = topic;
                endpoint_info.type_name = type;
                endpoint_info.node_name = node_name;
                endpoint_info.node_namespace = node_ns;
                endpoint_info.gid = gid;
                endpoint_info.qos = qos;

                // Register with GraphCache
                switch (kind) {
                    case DISCOVERY_ENTITY_PUBLISHER:
                        endpoint_info.type = EndpointType::PUBLISHER;
                        GraphCache::instance().register_publisher(
                            topic.c_str(),
                            type.c_str(),
                            node_name.c_str(),
                            node_ns.c_str(),
                            &qos,
                            &gid,
                            nullptr);  // impl_ptr not needed for daemon
                        break;

                    case DISCOVERY_ENTITY_SUBSCRIPTION:
                        endpoint_info.type = EndpointType::SUBSCRIPTION;
                        GraphCache::instance().register_subscription(
                            topic.c_str(),
                            type.c_str(),
                            node_name.c_str(),
                            node_ns.c_str(),
                            &qos,
                            &gid,
                            nullptr);
                        break;

                    case DISCOVERY_ENTITY_SERVICE:
                        endpoint_info.type = EndpointType::SERVICE;
                        GraphCache::instance().register_service(
                            topic.c_str(),
                            type.c_str(),
                            node_name.c_str(),
                            node_ns.c_str(),
                            &qos,
                            &gid,
                            nullptr);
                        break;

                    case DISCOVERY_ENTITY_CLIENT:
                        endpoint_info.type = EndpointType::CLIENT;
                        GraphCache::instance().register_client(
                            topic.c_str(),
                            type.c_str(),
                            node_name.c_str(),
                            node_ns.c_str(),
                            &qos,
                            &gid,
                            nullptr);
                        break;

                    default:
                        return {-EINVAL, {}};
                }

                // Phase 2.5.3: Broadcast to peers via DiscoveryManager
                DiscoveryManager::instance().broadcast_endpoint_added(endpoint_info);

                // Notify IPC clients of graph change
                uint64_t new_version = GraphCache::instance().get_graph_version();
                IpcServer::instance().notify_graph_changed(new_version);

                return {0, {}};
            }

            case DISCOVERY_IPC_MSG_UNREGISTER_ENDPOINT: {
                auto tlvs = tlv_parse(payload.data(), static_cast<uint32_t>(payload.size()));

                auto* gid_tlv = tlv_find(tlvs, DISCOVERY_TLV_GID);
                if (!gid_tlv) {
                    return {-EINVAL, {}};
                }

                rmw_gid_t gid;
                memset(&gid, 0, sizeof(gid));
                gid.implementation_identifier = rmw_get_implementation_identifier();
                tlv_as_bytes(*gid_tlv, gid.data, 24);

                GraphCache::instance().unregister_endpoint(&gid);

                // Phase 2.5.3: Broadcast removal to peers
                DiscoveryManager::instance().broadcast_endpoint_removed(gid);

                // Notify IPC clients
                uint64_t new_version = GraphCache::instance().get_graph_version();
                IpcServer::instance().notify_graph_changed(new_version);

                return {0, {}};
            }

            // ---- Query ----
            case DISCOVERY_IPC_MSG_GET_GRAPH_VERSION: {
                uint64_t version = GraphCache::instance().get_graph_version();
                std::vector<uint8_t> resp;
                // Return version as u32 (lower 32 bits, sufficient for version tracking)
                tlv_put_u32(resp, DISCOVERY_TLV_COUNT, static_cast<uint32_t>(version));
                return {0, resp};
            }

            case DISCOVERY_IPC_MSG_COUNT_MATCHED: {
                auto tlvs = tlv_parse(payload.data(), static_cast<uint32_t>(payload.size()));

                auto* topic_tlv = tlv_find(tlvs, DISCOVERY_TLV_TOPIC_NAME);
                auto* dir_tlv = tlv_find(tlvs, DISCOVERY_TLV_DIRECTION);

                if (!topic_tlv || !dir_tlv) {
                    return {-EINVAL, {}};
                }

                std::string topic = tlv_as_string(*topic_tlv);
                uint32_t direction = tlv_as_u32(*dir_tlv);

                size_t count = 0;
                if (direction == 0) {
                    // Count publishers
                    count = GraphCache::instance().count_publishers(topic.c_str());
                } else {
                    // Count subscribers
                    count = GraphCache::instance().count_subscribers(topic.c_str());
                }

                std::vector<uint8_t> resp;
                tlv_put_u32(resp, DISCOVERY_TLV_COUNT, static_cast<uint32_t>(count));
                return {0, resp};
            }

            default:
                return {-ENOSYS, {}};  // Not implemented
        }
}

}  // namespace ipc
}  // namespace rmw_dsoftbus
