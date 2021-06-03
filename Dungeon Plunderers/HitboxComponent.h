#pragma once
#include "vector"
#include "array"
#include "Hitbox.h"
class HitboxComponent
{
public:
	HitboxComponent();
	HitboxComponent(const Hitbox& hitbox);
	virtual ~HitboxComponent();
	void addHitbox(const Hitbox&& hitbox);
	void setHitbox(const int numberOfHitbox, const sf::Vector2f& Size, const sf::Vector2f& Offset);
	void setPositionOfHitbox(const int numberOfHitbox, const sf::Vector2f& Position);
	void setSizeOfHitbox(const int numberOfHitbox, const sf::Vector2f& Size);
	void setOffsetOfHitbox(const int numberOfHitbox, const sf::Vector2f& Offset);
	void moveHitbox(const int numberOfHitbox, const sf::Vector2f& Offset);
	void moveAllHitboxes(const sf::Vector2f& Offset);
	void setRotationOfAllHitboxes(const float rotation);
	void setScaleOfAllHitboxes(const sf::Vector2f& scale);
	bool intersects(const std::vector<Hitbox>& hitboxes) const;
	bool intersects(const sf::FloatRect& floatRect) const;
	bool intersects(const std::vector<sf::FloatRect>& floatRects) const;
	bool intersects(const HitboxComponent& hitboxComponent) const;
	bool intersects(const Hitbox& hitbox) const;
	bool intersectsSAT(const HitboxComponent& hitboxComponent) const;

	bool contains(const sf::Vector2f& Point) const;

	size_t size() const;
	void clearHitboxes();
	const std::vector<Hitbox>& getHitboxes() const;
	const Hitbox& operator[](int i) const;
	std::vector<Hitbox> hitboxes;

private:
	bool intersects(const Hitbox& h1, const sf::FloatRect& r2) const;
};

