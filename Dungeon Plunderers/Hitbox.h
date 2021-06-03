#pragma once
#include <SFML/Graphics.hpp>
#include <array>

bool& getShowHitboxes();

class Hitbox
	:public sf::Drawable
{
public:
	Hitbox(const sf::Vector2f& Position, const sf::Vector2f& Size, const sf::Vector2f& Offset = sf::Vector2f(0.f, 0.f), const sf::Color& color = sf::Color(255, 0, 0, 150));
	Hitbox(const sf::Vector2f& Position, const sf::Vector2f& Size, const sf::Vector2f& Offset, const sf::Vector2f& Origin);
	Hitbox();
	virtual ~Hitbox();
	void setHitbox(const sf::Vector2f& Size, const sf::Vector2f& Offset);
	void setPosition(const sf::Vector2f& Position);
	void setOffset(const sf::Vector2f& Offset);
	void setSize(const sf::Vector2f& Size);
	void setRotation(const float rotation);
	void setScale(const sf::Vector2f& scale);

	void move(const sf::Vector2f& Offset);
	float getLeft() const;
	float getRight() const;
	float getTop() const;
	float getBottom() const;
	sf::Vector2f getCenter() const;
	sf::Vector2f getScale() const;
	const sf::FloatRect& getGlobalBounds() const;
	const sf::Transform& getTransform() const;
	const sf::Vector2f& getOffset() const;
	sf::Vector2f getPoint(std::size_t index) const;

	bool contains(const sf::Vector2f& point) const;
	bool intersects(const Hitbox& hitbox2) const;
	bool intersects(const sf::FloatRect& floatRect) const;
	bool intersectsSAT(const Hitbox& hitbox2) const;
private:
	sf::RectangleShape hitbox;
	sf::Vector2f offset;
	sf::FloatRect globalBounds;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

