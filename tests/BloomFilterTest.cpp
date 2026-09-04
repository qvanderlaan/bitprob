#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

#include "probabilistic/BloomFilter.hpp"

static void testConstructor()
{
	probabilistic::BloomFilter filter(1'000, 0.01);

	assert(filter.expectedElements() == 1'000);
	assert(filter.bitCount() > 0);
	assert(filter.hashCount() > 0);
}

static void testInvalidArguments()
{
	bool threw = false;

	try
	{
		probabilistic::BloomFilter filter(0, 0.01);
	}
	catch (const std::invalid_argument&)
	{
		threw = true;
	}

	assert(threw);

	threw = false;

	try
	{
		probabilistic::BloomFilter filter(1'000, 0.0);
	}
	catch (const std::invalid_argument&)
	{
		threw = true;
	}

	assert(threw);

	threw = false;

	try
	{
		probabilistic::BloomFilter filter(1'000, 1.0);
	}
	catch (const std::invalid_argument&)
	{
		threw = true;
	}

	assert(threw);
}

static void testEmptyFilter()
{
	probabilistic::BloomFilter filter(1'000, 0.01);

	assert(!filter.possiblyContains("apple"));
	assert(!filter.possiblyContains("banana"));
	assert(!filter.possiblyContains("orange"));
}

static void testInsertedElements()
{
	probabilistic::BloomFilter filter(1'000, 0.01);

	filter.insert("apple");
	filter.insert("banana");
	filter.insert("orange");

	assert(filter.possiblyContains("apple"));
	assert(filter.possiblyContains("banana"));
	assert(filter.possiblyContains("orange"));
}

int main(void)
{
	testConstructor();
	testInvalidArguments();
	testEmptyFilter();
	testInsertedElements();

	std::cout << "All BloomFilter tests passed!" << std::endl;

	return (0);
}
