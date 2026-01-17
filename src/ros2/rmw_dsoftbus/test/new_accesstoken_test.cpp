/*
 * New AccessToken API Test
 * Tests the new C++ AccessTokenKit API on fresh KaihongOS system
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdint.h>
#include <string>

// Forward declarations for C++ API
namespace OHOS {
namespace Security {
namespace AccessToken {

// AccessTokenKit class methods (to be loaded via dlsym)
typedef uint64_t AccessTokenID;

// Function pointers for C++ methods
static uint64_t (*GetNativeTokenId_ptr)(const std::string& processName) = nullptr;
static int (*ReloadNativeTokenInfo_ptr)() = nullptr;

} // namespace AccessToken
} // namespace Security
} // namespace OHOS

using namespace OHOS::Security::AccessToken;

int main(int argc, char *argv[]) {
    fprintf(stderr, "=== New AccessToken API Test ===\n\n");

    // Step 1: Load AccessToken library
    fprintf(stderr, "[Step 1] Loading AccessToken library...\n");
    void *handle = dlopen("/system/lib64/chipset-pub-sdk/libaccesstoken_sdk.z.so", RTLD_NOW | RTLD_GLOBAL);
    if (!handle) {
        fprintf(stderr, "[ERROR] dlopen failed: %s\n", dlerror());
        return 1;
    }
    fprintf(stderr, "[OK] Library loaded\n");

    // Step 2: Try to resolve GetNativeTokenId (C++ mangled name)
    fprintf(stderr, "\n[Step 2] Resolving C++ symbols...\n");

    // The mangled name from nm output:
    // _ZN4OHOS8Security11AccessToken14AccessTokenKit16GetNativeTokenIdERKNSt3__h12basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEE
    // Which is: OHOS::Security::AccessToken::AccessTokenKit::GetNativeTokenId(std::string const&)

    void* getNativeTokenId_symbol = dlsym(handle, "_ZN4OHOS8Security11AccessToken14AccessTokenKit16GetNativeTokenIdERKNSt3__h12basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEE");

    if (getNativeTokenId_symbol) {
        fprintf(stderr, "[OK] GetNativeTokenId found: %p\n", getNativeTokenId_symbol);
        GetNativeTokenId_ptr = (uint64_t (*)(const std::string&))getNativeTokenId_symbol;
    } else {
        fprintf(stderr, "[ERROR] GetNativeTokenId not found\n");
        fprintf(stderr, "        Error: %s\n", dlerror());
    }

    // Step 3: Try ReloadNativeTokenInfo
    void* reloadSymbol = dlsym(handle, "_ZN4OHOS8Security11AccessToken14AccessTokenKit21ReloadNativeTokenInfoEv");
    if (reloadSymbol) {
        fprintf(stderr, "[OK] ReloadNativeTokenInfo found: %p\n", reloadSymbol);
        ReloadNativeTokenInfo_ptr = (int (*)())reloadSymbol;
    } else {
        fprintf(stderr, "[ERROR] ReloadNativeTokenInfo not found\n");
    }

    // Step 4: Try calling GetNativeTokenId
    if (GetNativeTokenId_ptr) {
        fprintf(stderr, "\n[Step 3] Calling GetNativeTokenId...\n");

        const char* process_name = (argc > 1) ? argv[1] : "com.huawei.ros2_test";
        fprintf(stderr, "[INFO] Process name: %s\n", process_name);

        try {
            std::string proc_str(process_name);
            uint64_t tokenId = GetNativeTokenId_ptr(proc_str);

            fprintf(stderr, "[RESULT] GetNativeTokenId returned: %llu (0x%llX)\n",
                    (unsigned long long)tokenId, (unsigned long long)tokenId);

            if (tokenId != 0) {
                fprintf(stderr, "✅ SUCCESS: Got non-zero token ID!\n");
                fprintf(stderr, "\n[INFO] This token ID can be used for:\n");
                fprintf(stderr, "  - Verifying process permissions\n");
                fprintf(stderr, "  - Querying token info\n");
                fprintf(stderr, "  - But NOT for SetSelfTokenID (API removed?)\n");
            } else {
                fprintf(stderr, "❌ Token ID is 0 (invalid)\n");
            }

        } catch (...) {
            fprintf(stderr, "[ERROR] Exception caught while calling GetNativeTokenId\n");
        }
    }

    // Step 5: Try ReloadNativeTokenInfo
    if (ReloadNativeTokenInfo_ptr) {
        fprintf(stderr, "\n[Step 4] Calling ReloadNativeTokenInfo...\n");
        try {
            int ret = ReloadNativeTokenInfo_ptr();
            fprintf(stderr, "[RESULT] ReloadNativeTokenInfo returned: %d\n", ret);
        } catch (...) {
            fprintf(stderr, "[ERROR] Exception caught while calling ReloadNativeTokenInfo\n");
        }
    }

    fprintf(stderr, "\n=== Conclusion ===\n");
    fprintf(stderr, "The new system uses C++ API only.\n");
    fprintf(stderr, "SetSelfTokenID API is removed or moved to different library.\n");
    fprintf(stderr, "Possible solutions:\n");
    fprintf(stderr, "  1. Use HAP application with permission declarations\n");
    fprintf(stderr, "  2. Find alternative permission injection method\n");
    fprintf(stderr, "  3. Run as system service with proper UID\n");

    return 0;
}
