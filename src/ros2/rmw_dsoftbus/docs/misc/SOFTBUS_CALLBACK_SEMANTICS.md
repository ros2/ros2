---
doc_id: softbus_callback_semantics
category: rmw_dsoftbus设计文档
title: SoftBus Callback 语义规约
description: rmw_dsoftbus 的 SoftBus 回调函数的语义契约和调用规则
priority: HIGH
last_updated: 2026-01-06
tags: [SoftBus, callback, 回调语义, 规约]
use_cases:
  - 理解 SoftBus 回调的调用时机和线程安全性
  - 实现正确的 rmw_dsoftbus 回调处理逻辑
  - 避免并发竞态条件问题
---

# SoftBus Callback Semantics - Empirical Contract for rmw_dsoftbus

## Purpose
Document empirically validated behavior of SoftBus session callbacks on rk3588s/OpenHarmony,
to justify assumptions used by discovery protocol v3.1 and future transport features.

## Callbacks of Interest
- OnSessionOpened(sessionId, result)
- OnSessionClosed(sessionId)
- OnBytesReceived(sessionId, data, dataLen)

## Assumptions Used by rmw_dsoftbus (Must Validate)
A1. Message atomicity: One SendBytes() -> One OnBytesReceived() with full payload (no fragmentation/coalescing)
A2. Threading: Callbacks may be invoked concurrently (reentrant) or serialized?
A3. Ordering: For a given sessionId, received messages preserve send order
A4. Lifecycle ordering: Opened occurs before first BytesReceived; Closed implies no further BytesReceived
A5. sessionId uniqueness: sessionId is unique per open session; may be reused after close?

## Validation Experiments

### E1: Atomicity / Framing
Method:
- Send N messages with unique (seq, payload_len) patterns.
- Receiver validates that each OnBytesReceived contains exactly one complete frame:
  - len == HEADER_SIZE + payload_len for discovery
- Record any cases of:
  - partial frames
  - multiple frames in one callback

Acceptance:
- 0 occurrences in 10k messages
If violated:
- Implement framing layer (length-prefix reassembly) for discovery channel.

### E2: Concurrency / Reentrancy
Method:
- In each callback, log thread id and timestamp, with a per-session active counter.
- Detect overlapping execution of callbacks (atomic increment/decrement).
Acceptance:
- Document whether callbacks are serialized or concurrent.
Action:
- If concurrent: all shared structures must be protected; avoid lock inversion.

### E3: Per-session ordering
Method:
- Sender emits strictly increasing seq per sessionId.
- Receiver checks monotonic increase for each session.
Acceptance:
- 0 reorder in 10k messages
If violated:
- Protocol must tolerate reorder (currently drops old seq; may need buffer or allow out-of-order).

### E4: Lifecycle ordering / late packets
Method:
- Force close session during high traffic.
- Observe if OnBytesReceived occurs after OnSessionClosed.
Acceptance:
- Define observed rule; if late packets exist:
  - Keep strict header checks and origin/sender checks (already present)
  - Ensure close path does not free resources prematurely.

### E5: sessionId reuse
Method:
- Repeated open/close cycles, record sessionId values.
Acceptance:
- Document whether sessionId reused.
Action:
- If reuse: mappings must be cleared strictly on close (already required).

## Results (Fill after device tests)
- A1: PASS/FAIL (evidence)
- A2: PASS/FAIL (evidence)
- A3: PASS/FAIL (evidence)
- A4: PASS/FAIL (evidence)
- A5: PASS/FAIL (evidence)

## Implementation Constraints Derived
- Lock ordering rules
- Framing requirement (if any)
- Shutdown sequence requirements

