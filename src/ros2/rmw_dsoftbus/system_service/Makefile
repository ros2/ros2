# Makefile for RMW Discovery System Service
# Target: System daemon for KaihongOS/OpenHarmony

TOOLCHAIN_ROOT = /home/jiusi/M-DDS/openharmony_prebuilts/gcc-linaro-7.5.0-2019.12-x86_64_aarch64-linux-gnu
CXX = $(TOOLCHAIN_ROOT)/bin/aarch64-linux-gnu-g++
STRIP = $(TOOLCHAIN_ROOT)/bin/aarch64-linux-gnu-strip

# Paths
RMW_DIR = ..
INC_DIR = $(RMW_DIR)/include
MOCK_INC = $(RMW_DIR)/mock_includes

# Compiler flags
CXXFLAGS = -std=c++14 -Wall -O2
CXXFLAGS += -I$(INC_DIR) -I$(MOCK_INC)
CXXFLAGS += -DUSE_REAL_SOFTBUS=1

# Linker flags
LDFLAGS = -pthread -static-libstdc++ -static-libgcc
# RPATH for system libraries
LDFLAGS += -Wl,-rpath,/system/lib64/platformsdk
LDFLAGS += -Wl,-rpath,/system/lib64
# Allow undefined symbols (SoftBus resolved at runtime)
LDFLAGS += -Wl,--unresolved-symbols=ignore-in-object-files
LDLIBS = -ldl

# Source files
DAEMON_SRCS = \
	rmw_discovery_daemon.cpp \
	$(RMW_DIR)/src/discovery_manager.cpp \
	$(RMW_DIR)/src/graph_cache.cpp \
	$(RMW_DIR)/src/native_token.cpp \
	$(RMW_DIR)/test/softbus_dlopen_shim.cpp

DAEMON_OBJS = $(patsubst %.cpp,%.o,$(DAEMON_SRCS))

# Target
TARGET = rmw_discovery_daemon

all: $(TARGET)

$(TARGET): $(DAEMON_OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)
	$(STRIP) $@
	@ls -lh $@
	@echo ""
	@echo "✅ System service daemon built: $(TARGET)"
	@echo "Size: $$(du -h $(TARGET) | cut -f1)"
	@echo ""
	@echo "Next steps:"
	@echo "  1. Deploy binary: cp $(TARGET) /system/bin/"
	@echo "  2. Deploy init.cfg: cp init/rmw_discovery.cfg /system/etc/init/"
	@echo "  3. Deploy token config: cp token/native_token_config.json /system/etc/token_sync/"
	@echo "  4. Reboot device: hdc shell reboot"
	@echo "  5. Verify: hdc shell 'ps -ef | grep rmw_discovery'"
	@echo ""

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(DAEMON_OBJS)

# Deploy to device (manual hdc commands)
deploy-prepare:
	@mkdir -p /mnt/c/tmp/rmw_service_deploy
	@cp $(TARGET) /mnt/c/tmp/rmw_service_deploy/
	@cp init/rmw_discovery.cfg /mnt/c/tmp/rmw_service_deploy/
	@cp token/native_token_config.json /mnt/c/tmp/rmw_service_deploy/
	@echo "Files prepared in /mnt/c/tmp/rmw_service_deploy/"
	@echo "Run deploy.sh to push to device"

.PHONY: all clean deploy-prepare
