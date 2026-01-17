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

// RMW Discovery System Service Daemon
// Runs as system service with proper token and permissions

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <atomic>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>
#include <thread>

#include "rmw_dsoftbus/discovery_manager.h"
#include "rmw_dsoftbus/graph_cache.h"
#include "rmw_dsoftbus/native_token.h"
#include "rmw_dsoftbus/ipc_server.h"

// Daemon state
static std::atomic<bool> g_running{true};
static std::thread g_ipc_thread;

// Signal handler
static void signal_handler(int sig) {
    fprintf(stderr, "[RMW Discovery Daemon] Received signal %d, shutting down...\n", sig);
    g_running = false;
}

// Daemonize process
static bool daemonize() {
    // Fork parent process
    pid_t pid = fork();
    if (pid < 0) {
        return false;
    }

    // Parent exits
    if (pid > 0) {
        exit(0);
    }

    // Child becomes session leader
    if (setsid() < 0) {
        return false;
    }

    // Fork again to prevent acquiring controlling terminal
    pid = fork();
    if (pid < 0) {
        return false;
    }

    if (pid > 0) {
        exit(0);
    }

    // Change working directory
    chdir("/");

    // Close standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Redirect to /dev/null or log file
    int fd = open("/data/log/rmw_discovery.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd >= 0) {
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        close(fd);
    }

    return true;
}

// Write PID file
static bool write_pid_file(const char* path) {
    FILE* f = fopen(path, "w");
    if (!f) {
        return false;
    }
    fprintf(f, "%d\n", getpid());
    fclose(f);
    return true;
}

int main(int argc, char** argv) {
    bool foreground = false;

    // Parse arguments
    if (argc > 1 && strcmp(argv[1], "-f") == 0) {
        foreground = true;
    }

    fprintf(stderr, "[RMW Discovery Daemon] Starting...\n");
    fprintf(stderr, "[RMW Discovery Daemon] Mode: %s\n", foreground ? "foreground" : "daemon");

    // Daemonize if not in foreground mode
    if (!foreground) {
        if (!daemonize()) {
            fprintf(stderr, "[RMW Discovery Daemon] Failed to daemonize\n");
            return 1;
        }
    }

    // Setup signal handlers
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGHUP, SIG_IGN);  // Ignore hangup

    // Write PID file
    write_pid_file("/var/run/rmw_discovery.pid");

    fprintf(stderr, "[RMW Discovery Daemon] PID: %d\n", getpid());
    fprintf(stderr, "[RMW Discovery Daemon] UID: %d GID: %d\n", getuid(), getgid());

    // Initialize Native Token (CRITICAL for SoftBus permissions)
    fprintf(stderr, "[RMW Discovery Daemon] Initializing Native Token...\n");
    bool token_ok = rmw_dsoftbus::try_init_native_token();
    if (!token_ok) {
        fprintf(stderr, "[RMW Discovery Daemon] WARNING: Native token initialization failed\n");
        fprintf(stderr, "[RMW Discovery Daemon] Continuing anyway (may fail permission check)\n");
    } else {
        fprintf(stderr, "[RMW Discovery Daemon] Native token initialized successfully\n");
    }

    // Initialize DiscoveryManager
    fprintf(stderr, "[RMW Discovery Daemon] Initializing DiscoveryManager...\n");
    bool init_ok = rmw_dsoftbus::DiscoveryManager::instance().initialize();
    if (!init_ok) {
        fprintf(stderr, "[RMW Discovery Daemon] FATAL: DiscoveryManager::initialize() failed\n");
        return 1;
    }
    fprintf(stderr, "[RMW Discovery Daemon] DiscoveryManager initialized successfully\n");

    // Initialize GraphCache
    rmw_dsoftbus::GraphCache::instance().initialize();
    fprintf(stderr, "[RMW Discovery Daemon] GraphCache initialized\n");

    // Initialize IPC Server (Phase 2.5.2)
    fprintf(stderr, "[RMW Discovery Daemon] Initializing IPC server...\n");
    rmw_dsoftbus::ipc::IpcServer::instance().initialize("/run/rmw_dsoftbus/discovery.sock");
    rmw_dsoftbus::ipc::IpcServer::instance().set_handler(rmw_dsoftbus::ipc::handle_ipc_request);

    // Note: No exception handling - OpenHarmony uses -fno-exceptions
    if (rmw_dsoftbus::ipc::IpcServer::instance().start()) {
        fprintf(stderr, "[RMW Discovery Daemon] IPC server socket created\n");

        // Start IPC server event loop in separate thread
        g_ipc_thread = std::thread([]() {
            fprintf(stderr, "[IPC Thread] Starting event loop\n");
            if (!rmw_dsoftbus::ipc::IpcServer::instance().run_loop()) {
                fprintf(stderr, "[IPC Thread] Event loop error: %s\n",
                        rmw_dsoftbus::ipc::IpcServer::instance().last_error());
            }
            fprintf(stderr, "[IPC Thread] Event loop exited\n");
        });

        fprintf(stderr, "[RMW Discovery Daemon] IPC server running on /run/rmw_dsoftbus/discovery.sock\n");
    } else {
        fprintf(stderr, "[RMW Discovery Daemon] WARNING: IPC server start failed: %s\n",
                rmw_dsoftbus::ipc::IpcServer::instance().last_error());
        fprintf(stderr, "[RMW Discovery Daemon] Continuing without IPC (cross-device only mode)\n");
    }

    // Print startup stats
    auto stats = rmw_dsoftbus::DiscoveryManager::instance().get_stats();
    fprintf(stderr, "[RMW Discovery Daemon] Startup stats: peers=%u\n", stats.peer_sessions_count);

    // Main service loop
    fprintf(stderr, "[RMW Discovery Daemon] Entering main service loop\n");
    fprintf(stderr, "[RMW Discovery Daemon] Service is now running (PID: %d)\n", getpid());

    int counter = 0;
    while (g_running) {
        sleep(30);  // Stats dump every 30 seconds
        if (!g_running) break;

        counter++;
        auto s = rmw_dsoftbus::DiscoveryManager::instance().get_stats();
        fprintf(stderr, "[RMW Discovery Daemon] Stats[%d]: peers=%u rx=%lu tx=%lu "
                "query=%lu snap=%lu drops=%lu\n",
                counter, s.peer_sessions_count, s.rx_total, s.tx_total,
                s.query_sent, s.snapshot_recv,
                s.drop_invalid + s.drop_dup + s.drop_parse_error);
    }

    // Shutdown
    fprintf(stderr, "[RMW Discovery Daemon] Shutting down...\n");

    // Shutdown IPC server
    rmw_dsoftbus::ipc::IpcServer::instance().shutdown();
    if (g_ipc_thread.joinable()) {
        g_ipc_thread.join();
        fprintf(stderr, "[RMW Discovery Daemon] IPC thread stopped\n");
    }

    // Final stats
    auto final_stats = rmw_dsoftbus::DiscoveryManager::instance().get_stats();
    fprintf(stderr, "[RMW Discovery Daemon] Final stats:\n");
    fprintf(stderr, "  Total RX: %lu TX: %lu\n", final_stats.rx_total, final_stats.tx_total);
    fprintf(stderr, "  Peers: %u\n", final_stats.peer_sessions_count);
    fprintf(stderr, "  Queries: %lu Snapshots: %lu\n", final_stats.query_sent, final_stats.snapshot_recv);

    // Shutdown DiscoveryManager
    rmw_dsoftbus::DiscoveryManager::instance().shutdown();

    // Remove PID file
    unlink("/var/run/rmw_discovery.pid");

    fprintf(stderr, "[RMW Discovery Daemon] Shutdown complete\n");
    return 0;
}
