# Design

## Goals

The main goal of `bitprob` is to provide a small and understandable implementation that can be used to investigate performance trade-offs.

The implementation therefore starts simple before introducing optimizations.

---

## Why C++?

C++ provides direct control over:

- memory layout
- integer arithmetic
- bit manipulation
- data structures
- compiler optimizations
- SIMD instructions

This makes it suitable for investigating the low-level behaviour of probabilistic data structures.

---

## Why `std::uint64_t`?

The Bloom filter stores bits in 64-bit words.

This provides a compact representation while allowing individual bits to be manipulated through native integer operations.

It also creates a natural foundation for future experiments involving:

- word-level operations
- batch processing
- SIMD
- cache behaviour

---

## Reference Implementation First

The first implementation intentionally prioritizes:

1. correctness
2. readability
3. measurable behaviour

Optimization comes afterwards.

This makes it possible to compare optimized implementations against a known-correct reference.

---

## Optimization Roadmap

Potential future optimizations include:

### Reduce modulo cost

The current implementation calculates:

```cpp
position = combined % bitCount;
```

Modulo can be relatively expensive depending on the generated machine code and whether the divisor is known at compile time.

Possible alternatives can be investigated later.

### Reduce branches

Lookup currently exits early when a required bit is zero.

This is good when negative lookups are common, but branch prediction behaviour should be measured rather than assumed.

### Batch processing

Instead of processing one element at a time:

```text
element → hash → probes → lookup
```

we can investigate:

```text
many elements → hashes → probes → lookups
```

This may provide opportunities for better instruction-level parallelism and SIMD.

### Cache behaviour

Bloom filters are memory-access heavy.

Randomly accessing a large bit array can cause cache misses.

Future benchmarks should investigate the relationship between:

```text
filter size
    ↓
cache level
    ↓
memory latency
    ↓
lookup throughput
```

---

## Design Principle

Every optimization should be supported by measurement.

The project should avoid optimizing based purely on intuition.
