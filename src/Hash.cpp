#include "probabilistic/Hash.hpp"

namespace probabilistic
{

constexpr std::uint64_t FNV_prime = 0x100000001b3;

// FNV-1a hash
[[nodiscard]]
std::uint64_t hash(std::string_view value) noexcept
{
	std::uint64_t hash = 0xcbf29ce484222325;

	for (uint8_t byteOfData : value)
	{
		hash ^= byteOfData;
		hash *= FNV_prime;
	}

	return (hash);
}

// Splitmix64-style mixing function
[[nodiscard]]
std::uint64_t hash2(std::uint64_t h) noexcept
{
	h ^= h >> 30;
	h *= 0xbf58476d1ce4e5b9ULL;
	h ^= h >> 27;
	h *= 0x94d049bb133111ebULL;
	h ^= h >> 31;

	return (h);
}

} // namespace probabilistic
