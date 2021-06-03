#pragma once
#include "TextButton.h"


namespace game {

	class MessageBox
		:public sf::Drawable
	{
	public:
		MessageBox(const sf::Vector2f& Position, const sf::Vector2f& Size, const sf::Vector2f& sizeOfButtons,
			const sf::Texture& BackgroundTexture, const sf::Texture& ButtonsTexture, const sf::Font& Font,
			const std::wstring& TextOfMessageBox, const std::wstring& TextOfFirstOptionButton, const std::wstring& TextOfSecondOptionButton);
		virtual ~MessageBox();
		bool FirstOptionWasPressed(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed);
		bool SecondOptionWasPressed(const sf::Vector2f& mousePosition, const bool wasMouseLeftButtonPressed);
		void update(const sf::Vector2f& mousePosition);
	private:
		sf::RectangleShape background;
		sf::Text text;
		TextButton firstOption;
		TextButton secondOption;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void alignButtons();
	};

}
