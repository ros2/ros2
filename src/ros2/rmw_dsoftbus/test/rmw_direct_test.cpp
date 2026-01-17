/*
 * RMW DSoftBus Direct Test
 *
 * 直接链接 librmw_dsoftbus.so，测试核心 API
 * 不使用 dlopen，避免静态链接冲突
 */

#include <stdio.h>
#include <stdlib.h>

// 直接声明 RMW 函数
extern "C" {
    const char* rmw_get_implementation_identifier(void);
}

int main() {
    printf("════════════════════════════════════════════════════════════\n");
    printf("  RMW DSoftBus Direct Test\n");
    printf("  No stub/mock - Real dsoftbus\n");
    printf("════════════════════════════════════════════════════════════\n\n");

    // Test 1: Get implementation identifier
    printf("[Test 1] Getting implementation identifier...\n");

    const char* impl_id = rmw_get_implementation_identifier();
    if (impl_id) {
        printf("  ✅ Implementation: %s\n", impl_id);
    } else {
        printf("  ❌ Failed to get identifier\n");
        return 1;
    }

    printf("\n════════════════════════════════════════════════════════════\n");
    printf("  ✅ Test PASSED\n");
    printf("════════════════════════════════════════════════════════════\n");

    return 0;
}
