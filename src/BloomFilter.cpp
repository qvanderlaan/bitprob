#include "probabilistic/BloomFilter.hpp"
#include "probabilistic/Hash.hpp"
#include <cmath>
#include <stdexcept>

namespace probabilistic
{

/**
 * @param n The amount of expected elements.
 * @param p The acceptable false positive rate {0...1} (e.g. 0.01 -> 1%)
 */
BloomFilter::BloomFilter(std::size_t n, double p)
	: _expectedElements(n)
{
	if (n == 0)
		throw std::invalid_argument("Expected elements must be greater than zero");

	if (p <= 0.0 || p >= 1.0)
		throw std::invalid_argument("False positive rate must be between 0 and 1");

	this->_bitCount =
		static_cast<std::size_t>(std::ceil(-static_cast<double>(n) * std::log(p) / std::pow(std::log(2.0), 2.0)));
	this->_hashCount = static_cast<std::size_t>(std::ceil((static_cast<double>(this->_bitCount) / n) * std::log(2.0)));

	const std::size_t wordCount = (this->_bitCount + 63) / 64;
	this->_bits.resize(wordCount, 0);
}

void BloomFilter::insert(std::string_view value)
{
	const std::uint64_t h1 = hash(value);
	const std::uint64_t h2 = hash2(h1);

	for (std::size_t i = 0; i < this->_hashCount; ++i)
	{
		const std::uint64_t combined = h1 + i * h2;
		const std::size_t position = combined % this->_bitCount;

		this->setBit(position);
	}
}

[[nodiscard]]
bool BloomFilter::possiblyContains(std::string_view value) const
{
	const std::uint64_t h1 = hash(value);
	const std::uint64_t h2 = hash2(h1);

	for (std::size_t i = 0; i < this->_hashCount; ++i)
	{
		const std::uint64_t combined = h1 + i * h2;
		const std::size_t position = combined % this->_bitCount;

		// this->setBit(position);
		if (!this->getBit(position))
			return (false);
	}

	return (true);
}

[[nodiscard]]
std::size_t BloomFilter::expectedElements(void) const noexcept
{
	return (this->_expectedElements);
}

[[nodiscard]]
std::size_t BloomFilter::bitCount(void) const noexcept
{
	return (this->_bitCount);
}

[[nodiscard]]
std::size_t BloomFilter::hashCount(void) const noexcept
{
	return (this->_hashCount);
}

void BloomFilter::setBit(std::size_t position) noexcept
{
	const std::size_t wordIndex = position / 64;
	const std::size_t bitIndex = position % 64;

	this->_bits[wordIndex] |= (1ULL << bitIndex);
}

[[nodiscard]]
bool BloomFilter::getBit(std::size_t position) const noexcept
{
	const std::size_t wordIndex = position / 64;
	const std::size_t bitIndex = position % 64;

	return ((this->_bits[wordIndex] & (1ULL << bitIndex)) != 0);
}

} // namespace probabilistic
