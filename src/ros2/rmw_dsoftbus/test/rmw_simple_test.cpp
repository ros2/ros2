/*
 * RMW DSoftBus Simple Test
 *
 * 简化版测试程序，只测试核心 API
 * 直接链接到 librmw_dsoftbus.so，使用真实 dsoftbus
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>

// 函数指针类型定义
typedef const char* (*get_impl_id_fn)(void);
typedef void* (*create_node_fn)(void*, const char*, const char*);
typedef int (*destroy_node_fn)(void*);
typedef int (*get_node_names_fn)(void*, void*, void*);

int main(int argc, char** argv) {
    printf("════════════════════════════════════════════════════════════\n");
    printf("  RMW DSoftBus Simple Test\n");
    printf("  Direct library test (no stub/mock)\n");
    printf("════════════════════════════════════════════════════════════\n\n");

    // ============================================================================
    // Step 1: Load librmw_dsoftbus.so
    // ============================================================================
    printf("[Step 1] Loading librmw_dsoftbus.so...\n");

    void* lib = dlopen("/data/librmw_dsoftbus.so.0.1.0", RTLD_NOW | RTLD_GLOBAL);
    if (!lib) {
        // Fallback to local path
        lib = dlopen("./librmw_dsoftbus.so.0.1.0", RTLD_NOW | RTLD_GLOBAL);
    }

    if (!lib) {
        fprintf(stderr, "  ❌ Failed to load library: %s\n", dlerror());
        return 1;
    }
    printf("  ✅ Library loaded\n");

    // ============================================================================
    // Step 2: Get implementation identifier
    // ============================================================================
    printf("\n[Step 2] Getting implementation identifier...\n");

    get_impl_id_fn rmw_get_impl = (get_impl_id_fn)dlsym(lib, "rmw_get_implementation_identifier");
    if (!rmw_get_impl) {
        fprintf(stderr, "  ❌ Failed to find rmw_get_implementation_identifier\n");
        dlclose(lib);
        return 1;
    }

    const char* impl_id = rmw_get_impl();
    printf("  ✅ Implementation: %s\n", impl_id);

    // ============================================================================
    // Step 3: List available symbols
    // ============================================================================
    printf("\n[Step 3] Testing symbol exports...\n");

    const char* test_symbols[] = {
        "rmw_init",
        "rmw_create_node",
        "rmw_destroy_node",
        "rmw_create_publisher",
        "rmw_create_subscription",
        "rmw_get_node_names",
        NULL
    };

    int found = 0;
    int total = 0;

    for (int i = 0; test_symbols[i]; i++) {
        total++;
        void* sym = dlsym(lib, test_symbols[i]);
        if (sym) {
            printf("  ✅ %s\n", test_symbols[i]);
            found++;
        } else {
            printf("  ❌ %s (not found)\n", test_symbols[i]);
        }
    }

    printf("\n  Result: %d/%d symbols found\n", found, total);

    // ============================================================================
    // Step 4: Cleanup
    // ============================================================================
    printf("\n[Cleanup] Closing library...\n");
    dlclose(lib);
    printf("  ✅ Done\n");

    printf("\n════════════════════════════════════════════════════════════\n");
    if (found == total) {
        printf("  ✅ Test PASSED - All symbols found\n");
    } else {
        printf("  ⚠️  Test PARTIAL - Some symbols missing\n");
    }
    printf("════════════════════════════════════════════════════════════\n");

    return (found == total) ? 0 : 1;
}
