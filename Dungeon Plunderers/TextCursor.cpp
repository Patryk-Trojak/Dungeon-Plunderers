#include "pch.h"
#include "TextCursor.h"

TextCursor::TextCursor(const sf::Vector2f& Position, const sf::Vector2f& Size)
	:timeOfDrawTextCursor(0)
{
	shape.setPosition(Position);
	shape.setSize(Size);
}

TextCursor::~TextCursor()
{
}

void TextCursor::update(const float deltaTime, const sf::Vector2f & Position)
{
	timeOfDrawTextCursor += deltaTime;
	if (timeOfDrawTextCursor > 1)
		timeOfDrawTextCursor = 0;
	shape.setPosition(Position);
}

void TextCursor::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if(timeOfDrawTextCursor > 0.5)
		target.draw(shape, states);
}
