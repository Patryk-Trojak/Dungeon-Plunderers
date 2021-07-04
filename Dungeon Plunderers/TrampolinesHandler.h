#pragma once
#include <vector>
#include "Trampoline.h"

class TrampolinesHandler
{
public:
    TrampolinesHandler(std::vector<Trampoline>& trampolines);

    void animateTrampolines(const float deltaTime);
    void drawTrampolines(sf::RenderTarget& target, float viewRightPos, float viewLeftPos) const;
    void setBlocksWhichTrampolinesStandingOn(const std::vector<Block>& blocks);
    void moveTrampolinesWithBlocks(float deltaTime);
private:
    std::vector<Trampoline>& trampolines;
};

