#include "pch.h"
#include "SupportGameState.h"


SupportGameState::SupportGameState(StateData& stateData)
	:State(stateData)
{
	text.setFont(stateData.resources.font);
	text.setString(L"Wsparcie jest DOBROWOLNE, jednak by³oby nam bardzo mi³o, gdybyœ Ty, Drogi Graczu, wspar³ nas finansowo\nJeszcze bardziej zmotywowa³oby to nas do tworzenia nowych gier oraz przyœpieszy³oby \npremiere naszej nastepnej gry(RPG 2D z ciekaw¹ i nietuzinkow¹ fabu³¹, \ntworzona tym razem na unreal engine 4, wiêc mamy nadziejê, ¿e bêdzie jeszcze lepsza!).\nDla naszych sponsorów przygotowaliœmy nastêpuj¹ce \"bonusy\":\nOd kwoty 5 z³: \n+Dodamamy twoje imiê i/lub nazwisko w naszej nastêpnej grze w zak³adce \"Sponsorzy\",\nktóra bêdziê znajdowaæ siê w menu\nOd kwoty 10 z³: \n+Bêdziesz mog³ stworzyæ NPC, którego dodamy do gry, w stworzonym przez nas edytorze \na swoje imiê i/lub nazwisko znajdziesz w zak³adce sponsorzy\nOd kwoty 20 z³:\n+Twoje imiê i/lub nick znajdzie sie w intrze w kategorii \"Sponsorzy glówni\".\nOtrzymasz równie¿ wszystkie wczeœniejsze wypisane bonusy\nJeœli zdecydujesz siê na wsparcie nas, prosimy wys³aæ dowoln¹ kwotê \nnanumer bankowy: 1234 1234 1234 1234 1234\noraz zrobiæ screenshoota przelewu, który wyœlesz nam na pocztê: Patis&GrzybekCompany@gmail.com\nWiadomoœæ ta, pomo¿e nam w nieprzeoczeniu twojego wsparcia. Z tej poczty bêdziemy siê równie¿ z tob¹ kontaktowaæ.");
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
