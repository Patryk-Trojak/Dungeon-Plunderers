#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Feedback 
	:public  sf::Drawable
{
public:
	Feedback(const sf::Vector2f& Position, const std::wstring textOfFeedback, const unsigned characterSize, const sf::Font& font);
	~Feedback();
	void update(const float deltaTime);
	float getTimeOfShowing() const;
private:
	sf::Text text;
	float timeOfShowing;
	float alphaColor;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


};

