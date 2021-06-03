#pragma once
#include<SFML/Graphics.hpp>
#include "Button.h"

class ScrollBar
	: public sf::Drawable
{
public:
	ScrollBar(const sf::Vector2f& Position, const sf::Vector2f& Size, 
		const float WindowHeight, const float PageHeight,
		const sf::Texture& TextureOfButtons);
	virtual ~ScrollBar();
	void update(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed, const int PageHeight, const float deltaTime);
	float getPercentValue() const;
	
	void moveViewY(const float offsetY);
	void moveViewToPositionY(const float PositionY);
private:
	sf::RectangleShape background;
	sf::RectangleShape scroller;
	Button up;
	Button down;
	float windowHeight;
	float pageHeight;

	void slideScroller(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed);
	void updateButtons(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed, const float deltaTime);
	void updateColorOfScroller(const sf::Vector2f& mousePosition);
	void updateSizeOfScroller();
	void moveScrollerToTargetPosition(const float deltaTime);
	void updatePositionOfScrollerIfBackgroundWasPressed(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed, const float deltaTime);
	void setPositionOfScrollerIfItIsOutOfBackground();

	bool slide;
	float targetPositionYOfScroller;
	float velocityYOfScroller;
	bool moveUp{ false };
	bool moveDown{ false };
	float timeOfClickBackground;

	sf::Vector2f lastMousePositionRelativeToDeskop;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

