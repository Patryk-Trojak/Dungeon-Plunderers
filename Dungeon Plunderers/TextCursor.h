#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class TextCursor
	:public sf::Drawable
{
public:
	TextCursor(const sf::Vector2f& Position, const sf::Vector2f& Size);
	~TextCursor();
	void update(const float deltaTime, const sf::Vector2f& Position);
private:
	sf::RectangleShape shape;
	float timeOfDrawTextCursor;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

