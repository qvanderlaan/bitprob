#pragma once

#include <cstdint>
#include <string_view>

namespace probabilistic
{

[[nodiscard]]
std::uint64_t hash(std::string_view value) noexcept;

[[nodiscard]]
std::uint64_t hash2(std::uint64_t h1) noexcept;

}; // namespace probabilistic
