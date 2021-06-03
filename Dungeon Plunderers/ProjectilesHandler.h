#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "EnemyProjectile.h"
#include "PlayerProjectile.h"
#include "MySimpleLibrary.hpp"


template <typename T>
class ProjectilesHandler
{
public:
	ProjectilesHandler(std::vector< std::unique_ptr< T > >& projectiles);
	void moveProjectiles(const float deltaTime);
	void animateProjectiles( const float deltaTime);
	void eraseProjectilesDependingOnTheirDistanceMoved();
	void drawProjectiles(sf::RenderTarget& target, float viewRightPos, float viewLeftPos) const;
private:
	std::vector< std::unique_ptr< T > >& projectiles;
};


template<typename T>
ProjectilesHandler<T>::ProjectilesHandler(std::vector<std::unique_ptr<T>>& projectiles)
	:projectiles(projectiles)
{
}

template <typename T>
void ProjectilesHandler<T>::moveProjectiles(const float deltaTime)
{
	for (auto const& i : projectiles)
	{
		i->update(deltaTime);
	}
}

template <typename T>
void ProjectilesHandler<T>::animateProjectiles(const float deltaTime)
{
	for (auto const& i : projectiles)
	{
		i->animate(deltaTime);
	}
}

template <typename T>
void ProjectilesHandler<T>::eraseProjectilesDependingOnTheirDistanceMoved()
{
	auto it = projectiles.begin();
	while (!projectiles.empty())
	{
		bool isLastProjectile = msl::isLastElement(projectiles, it);
		if (it->get()->getDistanceMoved() > it->get()->getDistanceOfErase())
		{
			*it = std::move(projectiles.back());
			projectiles.pop_back();
		}
		else
		{
			it++;
		}

		if (isLastProjectile)
			break;
	}
}

template <typename T>
void ProjectilesHandler<T>::drawProjectiles(sf::RenderTarget& target, float viewRightPos, float viewLeftPos) const
{
	for (auto const& i : projectiles)
	{
		if (i->getGlobalBoundsOfSprite().left < viewRightPos and i->getGlobalBoundsOfSprite().left + i->getGlobalBoundsOfSprite().width > viewLeftPos)
			target.draw(*i);
	}
}
