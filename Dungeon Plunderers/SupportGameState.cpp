#include "pch.h"
#include "SupportGameState.h"


SupportGameState::SupportGameState(StateData& stateData)
	:State(stateData)
{
	text.setFont(stateData.resources.font);
	text.setString(L"Wsparcie jest DOBROWOLNE, jednak by�oby nam bardzo mi�o, gdyby� Ty, Drogi Graczu, wspar� nas finansowo\nJeszcze bardziej zmotywowa�oby to nas do tworzenia nowych gier oraz przy�pieszy�oby \npremiere naszej nastepnej gry(RPG 2D z ciekaw� i nietuzinkow� fabu��, \ntworzona tym razem na unreal engine 4, wi�c mamy nadziej�, �e b�dzie jeszcze lepsza!).\nDla naszych sponsor�w przygotowali�my nast�puj�ce \"bonusy\":\nOd kwoty 5 z�: \n+Dodamamy twoje imi� i/lub nazwisko w naszej nast�pnej grze w zak�adce \"Sponsorzy\",\nkt�ra b�dzi� znajdowa� si� w menu\nOd kwoty 10 z�: \n+B�dziesz mog� stworzy� NPC, kt�rego dodamy do gry, w stworzonym przez nas edytorze \na swoje imi� i/lub nazwisko znajdziesz w zak�adce sponsorzy\nOd kwoty 20 z�:\n+Twoje imi� i/lub nick znajdzie sie w intrze w kategorii \"Sponsorzy gl�wni\".\nOtrzymasz r�wnie� wszystkie wcze�niejsze wypisane bonusy\nJe�li zdecydujesz si� na wsparcie nas, prosimy wys�a� dowoln� kwot� \nnanumer bankowy: 1234 1234 1234 1234 1234\noraz zrobi� screenshoota przelewu, kt�ry wy�lesz nam na poczt�: Patis&GrzybekCompany@gmail.com\nWiadomo�� ta, pomo�e nam w nieprzeoczeniu twojego wsparcia. Z tej poczty b�dziemy si� r�wnie� z tob� kontaktowa�.");
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::Green);
	text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(20, 20));
}


SupportGameState::~SupportGameState()
{
}

void SupportGameState::update(const float deltaTime)
{
	updateInput(deltaTime);
}

void SupportGameState::handleSFMLEvent(sf::RenderWindow& window, sf::Event& event)
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		resizeWindowProportionally(window, event);

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				stateData.states.pop();
			}
		}

	}
}

void SupportGameState::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(text, states);
}

void SupportGameState::updateInput(const float deltaTime)
{
}
