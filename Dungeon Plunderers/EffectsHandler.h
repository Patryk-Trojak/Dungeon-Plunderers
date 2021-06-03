#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Effect.h"
#include "MySimpleLibrary.hpp"


class EffectsHandler
{
public:
    EffectsHandler(std::vector<std::unique_ptr<Effect>>& effects);

    void drawEffects(sf::RenderTarget& target) const;
    void animateEffects(const float deltaTime);
    void deleteEffectIfIsOver();
private:
    std::vector< std::unique_ptr<Effect> >& effects;
};
