#include "pch.h"
#include "Feedback.h"

Feedback::Feedback(const sf::Vector2f& Position, const std::wstring textOfFeedback, const unsigned characterSize, const sf::Font& font)
	:text(textOfFeedback, font, characterSize),
	timeOfShowing(0)
{
	alphaColor = 0;
	text.setFillColor(sf::Color(255, 255, 255, alphaColor));
	text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color::Black);
	text.setPosition(990 - text.getGlobalBounds().width / 2, Position.y);
}

Feedback::~Feedback()
{
}

void Feedback::update(const float deltaTime)
{
	timeOfShowing += deltaTime;
	if (timeOfShowing < 1.5)
	{
		alphaColor += deltaTime * 2000;

		if (alphaColor > 255)
		{
			alphaColor = 255;
		}

		text.setFillColor(sf::Color(255, 255, 255, alphaColor));
		text.setOutlineColor(sf::Color(0, 0, 0, alphaColor));
	}
	else
	{
		alphaColor -= deltaTime * 200;

		if (alphaColor < 0)
		{
			alphaColor = 0;
		}

		text.setFillColor(sf::Color(255, 255, 255, alphaColor));
		text.setOutlineColor(sf::Color(0, 0, 0, alphaColor));
	}
}

float Feedback::getTimeOfShowing() const
{
	return timeOfShowing;
}

void Feedback::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text);
}
