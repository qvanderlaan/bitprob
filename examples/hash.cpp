#include <iostream>

#include "probabilistic/Hash.hpp"

int main(void)
{
	std::cout << probabilistic::hash("test") << std::endl;
	std::cout << probabilistic::hash("test2") << std::endl;
	std::cout << probabilistic::hash("quinten") << std::endl;
	std::cout << probabilistic::hash("test") << std::endl;
}
