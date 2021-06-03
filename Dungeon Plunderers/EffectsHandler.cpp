#include "pch.h"
#include "EffectsHandler.h"

EffectsHandler::EffectsHandler(std::vector<std::unique_ptr<Effect>>& effects)
    : effects(effects)
{}


void EffectsHandler::drawEffects(sf::RenderTarget& target) const
{
    for (auto const& i : effects)
        target.draw(*i);
}

void EffectsHandler::animateEffects(const float deltaTime)
{
    for (auto& i : effects)
        i->update(deltaTime);
}

void EffectsHandler::deleteEffectIfIsOver()
{
    auto effect = effects.begin();
    while (!effects.empty())
    {
        bool isLastEffect = msl::isLastElement(effects, effect);
        if (effect->get()->getIsOver())
        {
            *effect = std::move(effects.back());
            effects.pop_back();
        }
        else
        {
            effect++;
        }

        if (isLastEffect)
            break;
    }
}
