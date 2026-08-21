#include <iostream>

#include "probabilistic/BloomFilter.hpp"

int main(void)
{
	probabilistic::BloomFilter filter(1'000'000, 0.01);

	filter.insert("apple");
	filter.insert("banana");
	filter.insert("orange");

	std::cout << std::boolalpha;

	std::cout << "apple: " << filter.possiblyContains("apple") << std::endl;
	std::cout << "banana: " << filter.possiblyContains("banana") << std::endl;
	std::cout << "cucumber: " << filter.possiblyContains("cucumber") << std::endl;

	return (0);
}