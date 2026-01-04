// Copyright (c) 2026 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// Stub implementations for unsupported APIs
// - Events: UNSUPPORTED (out of scope)
// - Service/Client: UNSUPPORTED (out of scope)
// - Serialization: UNSUPPORTED (application layer responsibility)
//
// Note: Wait/Guard Condition APIs are now implemented in Level 3

#include "rmw_mock/types.h"
#include "rmw_mock/visibility.h"

#include "rmw/rmw.h"
#include "rmw/error_handling.h"

extern "C" {

//=============================================================================
// Event APIs (UNSUPPORTED - out of scope for mock)
//=============================================================================

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_publisher_event_init(
  rmw_event_t * rmw_event,
  const rmw_publisher_t * publisher,
  rmw_event_type_t event_type)
{
  (void)rmw_event;
  (void)publisher;
  (void)event_type;
  RMW_SET_ERROR_MSG("events not supported");
  return RMW_RET_UNSUPPORTED;
}

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_subscription_event_init(
  rmw_event_t * rmw_event,
  const rmw_subscription_t * subscription,
  rmw_event_type_t event_type)
{
  (void)rmw_event;
  (void)subscription;
  (void)event_type;
  RMW_SET_ERROR_MSG("events not supported");
  return RMW_RET_UNSUPPORTED;
}

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_event_set_callback(
  rmw_event_t * event,
  rmw_event_callback_t callback,
  const void * user_data)
{
  (void)event;
  (void)callback;
  (void)user_data;
  RMW_SET_ERROR_MSG("events not supported");
  return RMW_RET_UNSUPPORTED;
}

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_take_event(
  const rmw_event_t * event_handle,
  void * event_info,
  bool * taken)
{
  (void)event_handle;
  (void)event_info;
  (void)taken;
  RMW_SET_ERROR_MSG("events not supported");
  return RMW_RET_UNSUPPORTED;
}

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_event_fini(rmw_event_t * event)
{
  (void)event;
  RMW_SET_ERROR_MSG("events not supported");
  return RMW_RET_UNSUPPORTED;
}

//=============================================================================
// Service/Client APIs (UNSUPPORTED - out of scope for mock)
//=============================================================================

RMW_MOCK_PUBLIC
rmw_service_t *
rmw_create_service(
  const rmw_node_t * node,
  const rosidl_service_type_support_t * type_support,
  const char * service_name,
  const rmw_qos_profile_t * qos_policies)
{
  (void)node;
  (void)type_support;
  (void)service_name;
  (void)qos_policies;
  RMW_SET_ERROR_MSG("services not supported");
  return nullptr;
}

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_destroy_service(rmw_node_t * node, rmw_service_t * service)
{
  (void)node;
  (void)service;
  RMW_SET_ERROR_MSG("services not supported");
  return RMW_RET_UNSUPPORTED;
}

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_take_request(
  const rmw_service_t * service,
  rmw_service_info_t * request_header,
  void * ros_request,
  bool * taken)
{
  (void)service;
  (void)request_header;
  (void)ros_request;
  (void)taken;
  RMW_SET_ERROR_MSG("services not supported");
  return RMW_RET_UNSUPPORTED;
}

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_send_response(
  const rmw_service_t * service,
  rmw_request_id_t * request_header,
  void * ros_response)
{
  (void)service;
  (void)request_header;
  (void)ros_response;
  RMW_SET_ERROR_MSG("services not supported");
  return RMW_RET_UNSUPPORTED;
}

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_service_server_is_available(
  const rmw_node_t * node,
  const rmw_client_t * client,
  bool * is_available)
{
  (void)node;
  (void)client;
  (void)is_available;
  RMW_SET_ERROR_MSG("services not supported");
  return RMW_RET_UNSUPPORTED;
}

RMW_MOCK_PUBLIC
rmw_client_t *
rmw_create_client(
  const rmw_node_t * node,
  const rosidl_service_type_support_t * type_support,
  const char * service_name,
  const rmw_qos_profile_t * qos_policies)
{
  (void)node;
  (void)type_support;
  (void)service_name;
  (void)qos_policies;
  RMW_SET_ERROR_MSG("clients not supported");
  return nullptr;
}

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_destroy_client(rmw_node_t * node, rmw_client_t * client)
{
  (void)node;
  (void)client;
  RMW_SET_ERROR_MSG("clients not supported");
  return RMW_RET_UNSUPPORTED;
}

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_send_request(
  const rmw_client_t * client,
  const void * ros_request,
  int64_t * sequence_id)
{
  (void)client;
  (void)ros_request;
  (void)sequence_id;
  RMW_SET_ERROR_MSG("clients not supported");
  return RMW_RET_UNSUPPORTED;
}

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_take_response(
  const rmw_client_t * client,
  rmw_service_info_t * request_header,
  void * ros_response,
  bool * taken)
{
  (void)client;
  (void)request_header;
  (void)ros_response;
  (void)taken;
  RMW_SET_ERROR_MSG("clients not supported");
  return RMW_RET_UNSUPPORTED;
}

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_service_set_on_new_request_callback(
  rmw_service_t * service,
  rmw_event_callback_t callback,
  const void * user_data)
{
  (void)service;
  (void)callback;
  (void)user_data;
  RMW_SET_ERROR_MSG("services not supported");
  return RMW_RET_UNSUPPORTED;
}

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_client_set_on_new_response_callback(
  rmw_client_t * client,
  rmw_event_callback_t callback,
  const void * user_data)
{
  (void)client;
  (void)callback;
  (void)user_data;
  RMW_SET_ERROR_MSG("clients not supported");
  return RMW_RET_UNSUPPORTED;
}

//=============================================================================
// Serialization APIs (UNSUPPORTED - application layer responsibility)
//=============================================================================

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_serialize(
  const void * ros_message,
  const rosidl_message_type_support_t * type_support,
  rmw_serialized_message_t * serialized_message)
{
  (void)ros_message;
  (void)type_support;
  (void)serialized_message;
  RMW_SET_ERROR_MSG("serialization not supported in mock; serialize in application layer");
  return RMW_RET_UNSUPPORTED;
}

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_deserialize(
  const rmw_serialized_message_t * serialized_message,
  const rosidl_message_type_support_t * type_support,
  void * ros_message)
{
  (void)serialized_message;
  (void)type_support;
  (void)ros_message;
  RMW_SET_ERROR_MSG("deserialization not supported in mock; deserialize in application layer");
  return RMW_RET_UNSUPPORTED;
}

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_get_serialized_message_size(
  const rosidl_message_type_support_t * type_support,
  const rosidl_runtime_c__Sequence__bound * message_bounds,
  size_t * size)
{
  (void)type_support;
  (void)message_bounds;
  (void)size;
  RMW_SET_ERROR_MSG("serialization not supported");
  return RMW_RET_UNSUPPORTED;
}

//=============================================================================
// Subscription callback (UNSUPPORTED - requires executor integration)
//=============================================================================

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_subscription_set_on_new_message_callback(
  rmw_subscription_t * subscription,
  rmw_event_callback_t callback,
  const void * user_data)
{
  (void)subscription;
  (void)callback;
  (void)user_data;
  RMW_SET_ERROR_MSG("subscription callbacks not supported; use polling");
  return RMW_RET_UNSUPPORTED;
}

//=============================================================================
// Dynamic Type APIs (UNSUPPORTED)
//=============================================================================

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_take_dynamic_message(
  const rmw_subscription_t * subscription,
  rosidl_dynamic_typesupport_dynamic_data_t * dynamic_message,
  bool * taken,
  rmw_subscription_allocation_t * allocation)
{
  (void)subscription;
  (void)dynamic_message;
  (void)taken;
  (void)allocation;
  RMW_SET_ERROR_MSG("dynamic types not supported");
  return RMW_RET_UNSUPPORTED;
}

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_take_dynamic_message_with_info(
  const rmw_subscription_t * subscription,
  rosidl_dynamic_typesupport_dynamic_data_t * dynamic_message,
  bool * taken,
  rmw_message_info_t * message_info,
  rmw_subscription_allocation_t * allocation)
{
  (void)subscription;
  (void)dynamic_message;
  (void)taken;
  (void)message_info;
  (void)allocation;
  RMW_SET_ERROR_MSG("dynamic types not supported");
  return RMW_RET_UNSUPPORTED;
}

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_serialization_support_init(
  const char * serialization_lib_name,
  rcutils_allocator_t * allocator,
  rosidl_dynamic_typesupport_serialization_support_t * serialization_support)
{
  (void)serialization_lib_name;
  (void)allocator;
  (void)serialization_support;
  RMW_SET_ERROR_MSG("dynamic types not supported");
  return RMW_RET_UNSUPPORTED;
}

//=============================================================================
// QoS Profile APIs
//=============================================================================

RMW_MOCK_PUBLIC
rmw_ret_t
rmw_qos_profile_check_compatible(
  const rmw_qos_profile_t publisher_profile,
  const rmw_qos_profile_t subscription_profile,
  rmw_qos_compatibility_type_t * compatibility,
  char * reason,
  size_t reason_size)
{
  (void)publisher_profile;
  (void)subscription_profile;
  (void)reason;
  (void)reason_size;

  // Mock: always compatible (simplified)
  if (compatibility) {
    *compatibility = RMW_QOS_COMPATIBILITY_OK;
  }
  return RMW_RET_OK;
}

//=============================================================================
// Feature Support Query
//=============================================================================

RMW_MOCK_PUBLIC
bool
rmw_feature_supported(rmw_feature_t feature)
{
  // Mock supports minimal features
  switch (feature) {
    case RMW_FEATURE_MESSAGE_INFO_PUBLICATION_SEQUENCE_NUMBER:
    case RMW_FEATURE_MESSAGE_INFO_RECEPTION_SEQUENCE_NUMBER:
      return true;
    default:
      return false;
  }
}

}  // extern "C"
