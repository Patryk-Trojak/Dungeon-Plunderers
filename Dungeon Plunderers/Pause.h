#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include "Resources.h"
#include "MessageBox.h"

class Pause
    :public sf::Drawable
{
public:
    Pause(const Resources& resources);
    void handleButtonsOfMessagebox(const sf::Vector2f& mousePositionHUD, bool wasMousePressed, const std::function<void()>& exitGame);
    void updatePauseMessagebox(const sf::Vector2f& mousePositionHUD);
    bool isActive();
    void create(const sf::Vector2f& HUDViewCenter);
    void resume();
    bool wasExitGameButtonClicked(const sf::Vector2f& mousePositionHUD, bool wasMousePressed);
private:
    std::unique_ptr<game::MessageBox> pauseMessagebox;
    void createMessageBoxAboutPause(const sf::Vector2f& HUDViewCenter);
    bool active;
    const Resources& resources;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};




