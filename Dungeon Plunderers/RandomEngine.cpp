#include "pch.h"
#include "RandomEngine.h"

std::random_device RandomEngine::dev;
std::mt19937 RandomEngine::rng(RandomEngine::dev());

int RandomEngine::randInt(const int min, const int max)
{
	return std::uniform_int_distribution<int>{ min, max }(rng);
}
