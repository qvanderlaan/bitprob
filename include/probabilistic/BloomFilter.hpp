#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>
#include <vector>

namespace probabilistic
{

class BloomFilter
{
	private:
		std::vector<std::uint64_t> _bits;

		std::size_t _expectedElements;
		std::size_t _bitCount;
		std::size_t _hashCount;

	public:
		BloomFilter(std::size_t expectedElements, double falsePositiveRate);

		void insert(std::string_view value);

		[[nodiscard]]
		bool possiblyContains(std::string_view value) const;

		[[nodiscard]]
		std::size_t expectedElements(void) const noexcept;

		[[nodiscard]]
		std::size_t bitCount(void) const noexcept;

		[[nodiscard]]
		std::size_t hashCount(void) const noexcept;

	private:
		void setBit(std::size_t position) noexcept;

		[[nodiscard]]
		bool getBit(std::size_t position) const noexcept;
};

} // namespace probabilistic
