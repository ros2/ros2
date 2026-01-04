# rmw_mock Architecture Document

## Overview

`rmw_mock` is a mock RMW (ROS Middleware) implementation designed for testing `rclcpp` and `rcl` layers without real middleware dependencies.

## Design Principles

1. **Zero Middleware Dependencies**: No dsoftbus, FastDDS, or any transport layer
2. **Per-Context Router**: State isolated per `rmw_context_t`, enabling test isolation
3. **Condvar-based Wait**: Using `std::condition_variable` instead of `pipe/select`
4. **Progressive Implementation**: Level 1 → Level 2 → Level 3

## Level Definitions

### Level 1: Foundation/Smoke
- **Capability**: "Can be used, but cannot communicate"
- **APIs**: identifier, init/shutdown, context, node, graph stubs
- **Test**: `test_init_node` - node create/destroy lifecycle

### Level 2: Pub/Sub Core
- **Capability**: "Can communicate, but cannot schedule"
- **APIs**: publisher, subscription, serialized message publish/take
- **Constraint**: No blocking/wait mechanism (polling only)
- **Test**: `test_pubsub` - message routing via MockRouter

### Level 3: Executor/Wait
- **Capability**: "Semantically complete"
- **APIs**: wait_set, guard_condition (condvar-based)
- **Test**: `test_executor` - rclcpp::spin() can block and wake

## Core Components

### MockContext (per-context state)
```cpp
struct MockContext {
  std::atomic<bool> is_shutdown{false};
  std::atomic<uint64_t> gid_counter{1};
  MockRouter router;  // Per-context router instance
};
```

### MockRouter (per-context message router)
```cpp
struct MockRouter {
  std::map<topic, std::vector<SubscriptionImpl*>> topic_to_subscriptions;
  std::map<topic, std::vector<PublisherImpl*>> topic_to_publishers;
  std::condition_variable global_cv;  // Level 3 wait notification

  bool publish(topic, data, gid);
  void register_subscription(topic, sub);
  void clear_all();  // Called by rmw_context_fini
};
```

## File Structure

```
rmw_mock/
├── include/rmw_mock/
│   ├── types.h           # Core data structures
│   └── visibility.h      # Symbol export macros
├── src/
│   ├── level1/           # Foundation APIs
│   ├── level2/           # Pub/Sub APIs
│   └── level3/           # Wait/Guard APIs
├── test/
│   ├── level1/           # Level 1 acceptance tests
│   ├── level2/           # Level 2 acceptance tests
│   └── level3/           # Level 3 acceptance tests
├── BUILD.gn              # OHOS GN build
└── CMakeLists.txt        # Local development build
```

## Key Design Decisions

| Decision | Choice | Rationale |
|----------|--------|-----------|
| Router lifetime | Per-context | Test isolation, aligned with rmw_context_fini |
| Wait mechanism | condvar | OHOS FD risk mitigation, simpler |
| Level 2 boundary | No wake | Hard boundary: polling vs blocking |
| Event APIs | UNSUPPORTED | Focus on core, avoid version pitfalls |

## Implementation Status

- [x] Level 1: Foundation (complete)
- [x] Level 2: Pub/Sub Core (complete)
- [ ] Level 3: Executor/Wait (pending)

## Usage

```cpp
// Set RMW implementation
export RMW_IMPLEMENTATION=rmw_mock

// Run tests
./test_init_node    # Level 1: Foundation
./test_pubsub       # Level 2: Pub/Sub Core
./test_executor     # Level 3 (when ready)
```

---

**Last Updated**: 2026-01-05
**Version**: 0.1.0 (Level 1)
