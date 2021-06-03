#include "pch.h"
#include "ScrollBar.h"

ScrollBar::ScrollBar(const sf::Vector2f& Position, const sf::Vector2f& Size, 
	const float WindowHeight, const float PageHeight,
	const sf::Texture& TextureOfButtons)
	:background(Size),
	scroller(sf::Vector2f(Size.x , Size.y* (WindowHeight / PageHeight))),
	up(Position + sf::Vector2f(0, 0), sf::Vector2f(Size.x, Size.x), TextureOfButtons, sf::Vector2f(1, -1)),
	down(Position + sf::Vector2f(0, Size.y ), sf::Vector2f(Size.x, Size.x), TextureOfButtons),
	windowHeight(WindowHeight),
	velocityYOfScroller(0)
{
	scroller.setFillColor(sf::Color(67, 67, 67));
	background.setPosition(Position);
	
	scroller.setPosition(Position);
	background.setFillColor(sf::Color(37, 37, 37));
	targetPositionYOfScroller = scroller.getPosition().y;
}

ScrollBar::~ScrollBar()
{
}

void ScrollBar::update(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed, const int PageHeight, const float deltaTime)
{
	pageHeight = PageHeight;

	if ( scroller.getGlobalBounds().contains(mousePosition) and sf::Mouse::isButtonPressed(sf::Mouse::Left) )
		slide = true;
	else if( !sf::Mouse::isButtonPressed(sf::Mouse::Left) )
		slide = false;

	slideScroller(mousePosition, wasMouseLeftButtonPressed);
	updateButtons(mousePosition, wasMouseLeftButtonPressed, deltaTime);
	updateColorOfScroller( mousePosition);
	updateSizeOfScroller();
	moveScrollerToTargetPosition(deltaTime);
	updatePositionOfScrollerIfBackgroundWasPressed(mousePosition, wasMouseLeftButtonPressed, deltaTime);
	setPositionOfScrollerIfItIsOutOfBackground();

	lastMousePositionRelativeToDeskop = mousePosition;
}


float ScrollBar::getPercentValue() const
{
	if (scroller.getSize().y >= background.getSize().y)
		return 0;
	return (scroller.getPosition().y - background.getPosition().y) / (background.getSize().y - scroller.getSize().y) * 100;
}


void ScrollBar::moveViewY(const float offsetY)
{
	if (pageHeight != 0)
	{
		targetPositionYOfScroller += ((background.getSize().y - scroller.getSize().y) * offsetY) / pageHeight;
		velocityYOfScroller = 5 * (targetPositionYOfScroller - scroller.getPosition().y);
		if (targetPositionYOfScroller > scroller.getPosition().y)
		{
			moveDown = true;
			moveUp = false;

		}
		else
		{
			moveUp = true;
			moveDown = false;
		}
	}
}

void ScrollBar::moveViewToPositionY(const float PositionY)
{
	if (pageHeight != 0)
	{
		targetPositionYOfScroller = (((PositionY + 110) / pageHeight) * (background.getSize().y - scroller.getSize().y));
		velocityYOfScroller = 5 * (targetPositionYOfScroller - scroller.getPosition().y);
		if (targetPositionYOfScroller > scroller.getPosition().y)
		{
			moveDown = true;
			moveUp = false;

		}
		else
		{
			moveUp = true;
			moveDown = false;
		}
	}

}

void ScrollBar::slideScroller(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed)
{
	if (slide)
	{
		scroller.move(sf::Vector2f(0, mousePosition.y - lastMousePositionRelativeToDeskop.y));
		targetPositionYOfScroller = scroller.getPosition().y;
	}
}

void ScrollBar::updateButtons(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed, const float deltaTime)
{
	up.update(mousePosition);
	up.countTimeOfClick(mousePosition, wasMouseLeftButtonPressed, deltaTime);
	down.update(mousePosition);
	down.countTimeOfClick(mousePosition, wasMouseLeftButtonPressed, deltaTime);

	if (up.wasPressed(mousePosition, wasMouseLeftButtonPressed))
		moveViewY(-50);

	if (down.wasPressed(mousePosition, wasMouseLeftButtonPressed))
		moveViewY(50);

	if (up.getTimeOfClick() > 0.4f)
	{
		scroller.move(0.f, deltaTime * (-((background.getSize().y - scroller.getSize().y) * 500) / pageHeight));
		targetPositionYOfScroller = scroller.getPosition().y;
	}
	if (down.getTimeOfClick() > 0.4f)
	{
		scroller.move(0.f, deltaTime * (((background.getSize().y - scroller.getSize().y) * 500) / pageHeight));
		targetPositionYOfScroller = scroller.getPosition().y;
	}
}

void ScrollBar::updateColorOfScroller(const sf::Vector2f& mousePosition)
{
	scroller.setFillColor(sf::Color(67, 67, 67));
	if (scroller.getGlobalBounds().contains(mousePosition))
		scroller.setFillColor(sf::Color(101, 101, 101));
	if (slide)
		scroller.setFillColor(sf::Color(130, 130, 130));
}

void ScrollBar::updateSizeOfScroller()
{
	if (scroller.getSize().y > background.getSize().y / 20)
	{
		if (pageHeight == 0)
			scroller.setSize(sf::Vector2f(background.getSize().x, background.getSize().y));
		else
			scroller.setSize(sf::Vector2f(background.getSize().x, background.getSize().y - pageHeight / 10));
	}
	else
		scroller.setSize(sf::Vector2f(background.getSize().x, background.getSize().y / 20.f));
}

void ScrollBar::moveScrollerToTargetPosition(const float deltaTime)
{
	if (moveDown)
	{
		scroller.move(0.f, velocityYOfScroller * deltaTime);
		if (scroller.getPosition().y > targetPositionYOfScroller)
		{
			scroller.setPosition(scroller.getPosition().x, targetPositionYOfScroller);
			moveDown = false;
		}
	}
	if (moveUp)
	{
		scroller.move(0.f, velocityYOfScroller * deltaTime);
		if (scroller.getPosition().y < targetPositionYOfScroller)
		{
			scroller.setPosition(scroller.getPosition().x, targetPositionYOfScroller);
			moveUp = false;
		}
	}
}

void ScrollBar::updatePositionOfScrollerIfBackgroundWasPressed(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed, const float deltaTime)
{
	if ((background.getGlobalBounds().contains(mousePosition) and !scroller.getGlobalBounds().contains(mousePosition)) and wasMouseLeftButtonPressed)
	{
		if (mousePosition.y > scroller.getPosition().y)
			moveViewY(500);
		else
			moveViewY(-500);
	}
	if ((background.getGlobalBounds().contains(mousePosition) and !scroller.getGlobalBounds().contains(mousePosition)) and sf::Mouse::isButtonPressed(sf::Mouse::Left))
		timeOfClickBackground += deltaTime;
	else
		timeOfClickBackground = 0;

	if (timeOfClickBackground > 0.4f)
	{
		if (mousePosition.y > scroller.getPosition().y)
			scroller.move(0.f, deltaTime * 20.f * (((background.getSize().y - scroller.getSize().y) * 500) / pageHeight));
		else
			scroller.move(0.f, deltaTime * 20.f * (-((background.getSize().y - scroller.getSize().y) * 500) / pageHeight));

		targetPositionYOfScroller = scroller.getPosition().y;
	}
}

void ScrollBar::setPositionOfScrollerIfItIsOutOfBackground()
{
	if (scroller.getSize().y != background.getSize().y)
	{
		if (scroller.getPosition().y < background.getPosition().y)
		{
			targetPositionYOfScroller = scroller.getPosition().y;
			scroller.setPosition(sf::Vector2f(scroller.getPosition().x, background.getPosition().y));
		}
		if (scroller.getPosition().y + scroller.getSize().y > background.getPosition().y + background.getSize().y)
		{
			targetPositionYOfScroller = scroller.getPosition().y;
			scroller.setPosition(sf::Vector2f(scroller.getPosition().x, background.getPosition().y + background.getSize().y - scroller.getSize().y));
		}
	}
	else
	{
		scroller.setPosition(sf::Vector2f(scroller.getPosition().x, background.getPosition().y));
		targetPositionYOfScroller = scroller.getPosition().y;
	}
}


void ScrollBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(scroller, states);
	target.draw(up, states);
	target.draw(down, states);

}
