# Bloom Filter

## Introduction

A Bloom filter is a probabilistic data structure for testing set membership.

It can answer:

> "Is this element possibly in the set?"

with two possible outcomes:

```text
false → definitely not present
true  → possibly present
```

A Bloom filter cannot produce false negatives when implemented correctly, but it can produce false positives.

---

## Bit Array

The filter consists of a bit array:

```
00000000 00000000 00000000 00000000 ...
```

Initially every bit is zero.

When inserting an element, several hash functions determine which bits should be set.

For example:

```text
hash 1 → bit 5
hash 2 → bit 19
hash 3 → bit 27
```

The filter becomes:

```text
00000100 00000000 00001000 00000010
```

The actual implementation stores these bits inside:

```cpp
std::vector<std::uint64_t>
```

---

## Insertion

For an element `x`, we calculate hash values:

$$
h_1(x)
$$

and

$$
h_2(x)
$$

Then generate `k` probe positions:

$$
g_i(x) = h_1(x) + i h_2(x)
$$

Each position is mapped into the bit array:

$$
position_i = g_i(x) \bmod m
$$

where `m` is the number of bits.

Each resulting bit is set to `1`.

---

## Lookup

To check whether an element exists, the same positions are calculated.

If any required bit is zero:

```text
→ definitely not present
```

If every required bit is set:

```text
→ possibly present
```

The filter cannot determine whether those bits were set by this particular element or by other elements.

This is the source of false positives.

---

## Memory Calculation

For:

* `n` expected elements
* `p` target false-positive probability

the required number of bits is:

$$
m = -\frac{n\ln(p)}{(\ln 2)^2}
$$

For example:

```text
n = 1,000,000
p = 0.01
```

requires approximately:

```text
9.6 million bits
```

or roughly:

```text
1.2 MB
```

before accounting for implementation-level details such as word rounding.

---

## Number of Hash Probes

The optimal number of probes is:

$$
k = \frac{m}{n}\ln 2
$$

Increasing `k` is not always better.

More probes can reduce false positives, but each additional probe also requires:

* more hashing work
* more arithmetic
* another memory access

This creates an interesting memory-vs-CPU trade-off.

---

## Expected False-Positive Rate

After inserting `n` elements into a filter with `m` bits and `k` probes, the approximate false-positive probability is:

$$
p \approx
\left(1-e^{-kn/m}\right)^k
$$

One of the goals of `bitprob` is to compare this theoretical value against measurements from the actual implementation.

---

## Implementation

The bit array is represented as:

```cpp
std::vector<std::uint64_t> _bits;
```

A logical bit position is converted into:

```cpp
wordIndex = position / 64;
bitIndex = position % 64;
```

Setting a bit:

```cpp
_bits[wordIndex] |= (1ULL << bitIndex);
```

Checking a bit:

```cpp
(_bits[wordIndex] & (1ULL << bitIndex)) != 0
```

This keeps the actual storage compact while exposing a logical array of individual bits.

---

## Future Experiments

Possible experiments include:

* different target false-positive rates
* different filter sizes
* different numbers of probes
* alternative hash functions
* sequential vs random access
* cache behaviour
* branchless lookup
* batch lookup
* SIMD implementations
