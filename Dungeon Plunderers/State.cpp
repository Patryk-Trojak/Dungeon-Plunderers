#include "pch.h"
#include "State.h"

State::State(StateData& stateData)
	:stateData(stateData),
	numberOfStatesPop(0),
	WereSettingsChanged(false),
	backToPreviousState(sf::Vector2f(30.f, 1000.f), sf::Vector2f(130.f, 50.f), stateData.resources[TextureID::BackButton], stateData.resources.font,
		L"Wróæ", 40, ContentAlignment::left, 49.f)
{
	//view.setSize(1500, 1000);

	//1600 900           
	background.setTexture(stateData.resources[TextureID::BackgroundGame]);
	background.setTextureRect(sf::IntRect(0, 0, 1920, 1080));

	view.setSize(1920, 1080);
	view.setCenter(1920 / 2, 1080 / 2);
	HUDView = view;
	closeWindow = false;
	wasMousePressed = false;
	HasCustomCursor = false;
	lastWindowSize = sf::Vector2u(stateData.settings.windowSize.x, stateData.settings.windowSize.y);
}


State::~State()
{
}


void State::updateMousePositions(sf::RenderWindow& window)
{
	window.setView(view);
	mousePositionView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	window.setView(HUDView);
	mousePositionHUD = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	window.setView(view);

}


const sf::View& State::getView() const
{
	return view;
}

const sf::View& State::getHUDView() const
{
	return HUDView;
}


bool State::getCloseWindow()
{
	return closeWindow;
}

bool State::hasCustomCursor()
{
	return HasCustomCursor;
}

int State::getNumberOfStatesPop() const
{
	return numberOfStatesPop;
}

bool State::wereSettingsChanged()
{
	return WereSettingsChanged;
}


void State::updateBackToPreviousState()
{
	backToPreviousState.update(mousePositionView);
	if (backToPreviousState.wasPressed(mousePositionView, wasMousePressed))
	{
		numberOfStatesPop = 1;
	}
}

void State::resizeWindowProportionally(sf::RenderWindow& window, sf::Event& event)
{
	if (event.type == sf::Event::Resized)
	{
		if (stateData.settings.resizeProportionally)
		{
			if (lastWindowSize.y != event.size.height)
			{
				window.setSize(sf::Vector2u(event.size.height * 16 / 9, event.size.height));

			}
			else
				window.setSize(sf::Vector2u(event.size.width, event.size.width * 9 / 16));

		}
		lastWindowSize = sf::Vector2u(event.size.width, event.size.height);
		stateData.settings.windowSize = window.getSize();
		PersistenceSaver::save(stateData.settings);

		 
	}
	

}

