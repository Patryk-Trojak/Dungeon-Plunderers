#pragma once
#include <random>

class RandomEngine
{
public:
	static int randInt(const int min, const int max);

private:
	static std::random_device dev;
	static std::mt19937 rng;
};

