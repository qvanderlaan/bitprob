# bitprob
High-performance probabilistic data structures in modern C++, exploring the trade-offs between memory, accuracy, and CPU performance.

> **Status:** Early development

## Overview

`bitprob` is a small C++ library for experimenting with probabilistic data structures and the trade-offs behind them.

The project currently focuses on a Bloom filter implemented from scratch using:
- C++ 17
- bit-level storage using `std::uint64_t`
- FNV-1a hashing
- SplitMix64-style integer mixing
- double hashing
- configurable false-positive probability

The goal of this project is not to provide the largest or most feature-complete Bloom filter library, but to understand what happens underneath an abstraction:

- How much memory does a probabilistic data structure actually need?
- How does the false-positive rate behave in practice?
- How does the number of hash probes affect performance?
- What impact do memory access patterns have?
- Can batch operations benefit from SIMD?
- Where are the actual performance bottlenecks?

---

## Current Features

### Bloom Filter

The current implementation provides:

```cpp
probabilistic::BloomFilter filter(1'000'000, 0.01);

filter.insert("apple");

if (filter.possiblyContains("apple"))
{
    // Possibly present
}
```

A Bloom filter guarantees:
- No false negatives
- Possible false positives

In other words:

```
possiblyContains(x) == false
    → definitely not present

possiblyContains(x) == true
    → probably present
```

## Quick Start

### Requirements

- C++ 17 compatible compiler
- Make

### Build

```bash
make
```

### Run the example
```bash
make run
```

### Run the tests
```bash
make test
```

---

## Example

```c++
#include <iostream>

#include "probabilistic/BloomFilter.hpp"

int main(void)
{
    probabilistic::BloomFilter filter(1'000'000, 0.01);

    filter.insert("apple");
    filter.insert("banana");
    filter.insert("orange");

    std::cout << std::boolalpha;

    std::cout << "apple: "
              << filter.possiblyContains("apple")
              << std::endl;

    std::cout << "banana: "
              << filter.possiblyContains("banana")
              << std::endl;

    std::cout << "cucumber: "
              << filter.possiblyContains("cucumber")
              << std::endl;

    return (0);
}
```


---

## How It Works

A Bloom filter represents a set using a bit array and multiple hash probes.

For an expected number of elements `n` and target false-positive probability `p`, the required number of bits is approximately:

$$
m = -\frac{n\ln(p)}{(\ln 2)^2}
$$

The optimal number of hash probes is approximately:

$$
k = \frac{m}{n}\ln 2
$$

`bitprob` stores the bit array as 64-bit words:

```text
std::vector<std::uint64_t>
```

A bit position is translated into:

```text
word index = position / 64
bit index  = position % 64
```

This allows individual bits to be manipulated using integer operations and bit shifting.

For more details, see:

* [Bloom Filter](docs/bloom-filter.md)
* [Hashing](docs/hashing.md)
* [Design](docs/design.md)

---

## Hashing

The current implementation uses two hash values:

```text
h1(x)
h2(x)
```

which are combined using double hashing:

$$
g_i(x) = h_1(x) + i h_2(x)
$$

Each resulting value determines a bit position in the filter.

This allows multiple hash probes to be generated from two base hash functions rather than calculating a completely independent hash for every probe.

See [Hashing](docs/hashing.md) for the implementation details and reasoning behind the current approach.

---

## Testing

The project contains tests for the core Bloom filter behaviour.

Current tests cover:

* constructor validation
* filter configuration
* empty filters
* inserted elements
* absence of false negatives

The next stage is to measure the actual false-positive rate against the configured target.

---

## Performance

Performance is an explicit part of the project.

Rather than optimizing blindly, the project aims to measure the effect of:

* number of hash probes
* integer arithmetic
* modulo operations
* memory access patterns
* cache behaviour
* branch prediction
* bit manipulation
* batch processing
* SIMD

---

## Project Goals

The project is developed in several stages.

### 1. Correctness

Build a simple and understandable reference implementation.

### 2. Measurement

Measure:

* false-positive rate
* memory usage
* insertion throughput
* lookup throughput

### 3. Optimization

Investigate:

* cache locality
* branch behaviour
* integer arithmetic
* memory access
* hashing cost
* SIMD and batch processing

### 4. Comparison

Compare different implementation strategies and document their trade-offs.

---

## License

This project is licensed under the MIT License.
See [LICENSE](LICENSE) for details.
