#pragma once
#include<SFML/Graphics.hpp>
#include<cmath>
#include"Button.h"

class Slider
	: public sf::Drawable
{
public:
	Slider(const sf::Vector2f& Position, const sf::Vector2f& Size, const float min, const float max, const float innitialValue,
		const sf::Texture& textureOfSlider, const sf::Texture& textureOfAxis, const sf::Texture& textureOfButtons, const sf::Font& font);
	virtual ~Slider();
	void update(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed, const float deltaTime);
	void setPosition(const sf::Vector2f& Position);
	sf::Vector2f getPosition() const;
	float getValue() const;
	void setMin(const float newMin);
	void setMax(const float newMax);
	void setValue(const float newValue);
	bool isSliding() const;
	bool wasValueChanged() const;
	bool isMouseOver(const sf::Vector2f& mousePosition) const;
private:
	sf::RectangleShape slider;
	sf::RectangleShape axis;
	Button increaser;
	Button decreaser;
	sf::Text Value;
	float value;
	float lastValue;
	float min;
	float max;
	bool slide;
	bool wasSlided;
	bool WasValueChanged;
	float PositionXOfAxisRelativeToSlider;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override; 	
};

