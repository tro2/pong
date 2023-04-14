#include "Utils.h"
#include <cmath>
#include <random>

double Utils::randomDouble(double lowerBound, double upperBound)
{
	// random device for randomization functions
	static std::random_device rand;

	// randomization engine
	static std::default_random_engine eng(rand());
	
	std::uniform_real_distribution<double> distr(lowerBound, upperBound);

	return distr(eng);
}

int Utils::randomInt(int lowerBound, int upperBound)
{
	// random device for randomization functions
	static std::random_device rand;

	// randomization engine
	static std::default_random_engine eng(rand());
	
	std::uniform_int_distribution<int> distr(lowerBound, upperBound);

	return distr(eng);
}

int Utils::preciseAdd(int a, double b)
{
	double preciseA = a;
	preciseA += b;

	return static_cast<int>(round(preciseA));
}
