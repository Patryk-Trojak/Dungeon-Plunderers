#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum class ContentAlignment{center = 0, left, right};
enum class ButtonState{idle = 0, hover};

class Button 
	:public sf::Drawable
{
public:
	Button(const sf::Vector2f& Position, const sf::Vector2f& Size,
		   const sf::Texture& Texture, const sf::Vector2f& Scale = sf::Vector2f(1, 1),
		   const sf::Color IdleColor = sf::Color::White, const sf::Color HoverColor = sf::Color::Red);
	virtual ~Button();
	void update(const sf::Vector2f& mousePosition);
	bool wasPressed(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed) const;
	void setPosition(const sf::Vector2f& Position);
	void setCurrentColor(const sf::Color& color);
	void setIdleColor(const sf::Color& color);
	void setHoverColor(const sf::Color& color);
	
	sf::Vector2f getPosition() const;
	bool isMouseOverButton(const sf::Vector2f& mousePosition) const;
	sf::Vector2f getSize() const;
	void setSize(const sf::Vector2f& size);
	void countTimeOfClick(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed, const float deltaTime);
	float getTimeOfClick() const;
protected:
	sf::RectangleShape shape;
	sf::Color IdleColor;
	sf::Color HoverColor;
	ButtonState state;
	float timeOfClick;
	bool isClicked;
	void updateColorByButtonState();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

