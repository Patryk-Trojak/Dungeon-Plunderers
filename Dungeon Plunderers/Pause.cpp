#include "pch.h"
#include "Pause.h"


Pause::Pause(const Resources& resources)
    : resources(resources), active(false)
{}

void Pause::handleButtonsOfMessagebox(const sf::Vector2f& mousePositionHUD, bool wasMousePressed, const std::function<void()>& exitGame)
{
    if (isActive())
    {
        if (pauseMessagebox->FirstOptionWasPressed(mousePositionHUD, wasMousePressed))
        {
            pauseMessagebox.reset();
            active = false;
        }
        else if (pauseMessagebox->SecondOptionWasPressed(mousePositionHUD, wasMousePressed))
        {
            exitGame();
        }
    }
}

bool Pause::wasExitGameButtonClicked(const sf::Vector2f& mousePositionHUD, bool wasMousePressed)
{
    if(pauseMessagebox)
        return pauseMessagebox->SecondOptionWasPressed(mousePositionHUD, wasMousePressed);
    return false;
}

void Pause::updatePauseMessagebox(const sf::Vector2f& mousePositionHUD)
{
    if (pauseMessagebox)
    {
        pauseMessagebox->update(mousePositionHUD);
    }
}

bool Pause::isActive()
{
    return active;
}
void Pause::create(const sf::Vector2f& HUDViewCenter)
{
    createMessageBoxAboutPause(HUDViewCenter);
    active = true;
}
void Pause::createMessageBoxAboutPause(const sf::Vector2f& HUDViewCenter)
{
    pauseMessagebox = std::make_unique<game::MessageBox>(HUDViewCenter, sf::Vector2f(685, 200), sf::Vector2f(100, 55),
        resources[TextureID::MessageboxBackground], resources[TextureID::GreyButton100x50], resources.font,
        L"Na pewno chcesz zakoñczyæ granie?", L"Graj dalej", L"WyjdŸ");
}

void Pause::resume()
{
    pauseMessagebox.reset();
    active = false;
}

void Pause::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (pauseMessagebox)
    {
        target.draw(*pauseMessagebox);
    }
}
