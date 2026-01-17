// Minimal test to diagnose initialize() blocking issue

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <thread>
#include <atomic>
#include <chrono>

#include "rmw_dsoftbus/discovery_manager.h"
#include "rmw_dsoftbus/native_token.h"

static std::atomic<bool> init_complete{false};
static std::atomic<bool> timeout_reached{false};

void timeout_handler(int sig) {
    (void)sig;
    fprintf(stderr, "[TIMEOUT] initialize() took too long (>5 seconds)\n");
    fflush(stderr);
    timeout_reached = true;
}

int main() {
    fprintf(stderr, "=== Minimal Initialize Diagnostic ===\n");
    fprintf(stderr, "[MAIN] Starting...\n");
    fflush(stderr);

    // Set 5-second timeout
    signal(SIGALRM, timeout_handler);
    alarm(5);

    fprintf(stderr, "[MAIN] About to call initialize()...\n");
    fflush(stderr);

    // Call initialize
    bool result = rmw_dsoftbus::DiscoveryManager::instance().initialize();

    init_complete = true;
    alarm(0);  // Cancel alarm

    fprintf(stderr, "[MAIN] initialize() returned: %s\n", result ? "true" : "false");
    fflush(stderr);

    if (timeout_reached) {
        fprintf(stderr, "[ERROR] Timeout during initialize()\n");
        fflush(stderr);
        return 1;
    }

    fprintf(stderr, "[MAIN] Test completed successfully\n");
    fflush(stderr);

    // Clean shutdown
    rmw_dsoftbus::DiscoveryManager::instance().shutdown();

    return result ? 0 : 1;
}
