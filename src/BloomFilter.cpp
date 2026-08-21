#include "probabilistic/BloomFilter.hpp"
#include <cmath>
#include <iostream>

namespace probabilistic
{

/**
 * @param n The amount of expected elements.
 * @param p The acceptable false positive rate {0...1} (e.g. 0.01 -> 1%)
 */
BloomFilter::BloomFilter(std::size_t n, double p)
	: _elementCount(n)
{
	this->_bitCount = -static_cast<double>(n) * std::log(p) / std::pow(std::log(2.0), 2.0);
	this->_hashCount = static_cast<std::size_t>((static_cast<double>(this->_bitCount) / n) * std::log(2.0));

	std::cout << "Bit count: " << _bitCount << std::endl;
	std::cout << "Hash count: " << this->_hashCount << std::endl;
}

void BloomFilter::insert(std::string_view value)
{
	//
}

[[nodiscard]]
bool BloomFilter::possiblyContains(std::string_view value) const
{
	//
}

[[nodiscard]]
std::size_t BloomFilter::size(void) const noexcept
{
	//
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

} // namespace probabilistic
