#include "pch.h"
#include "Boss.h"

Boss::Boss() 
	: rng(dev())
{

}

int Boss::rand(const int min, const int max)
{
	return std::uniform_int_distribution<int>{ min, max }(rng);
}
