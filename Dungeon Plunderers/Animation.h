#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Animation
{
public:
	Animation(const int StartFrameX, const int StartFrameY, const sf::Vector2i& SizeOfSingleFrame, const int NumberOfFrames, float TimeOfFrameChange, bool repeated = true, const int StartRepeatedFrame = 1);
	Animation();
	virtual ~Animation();
	void play(sf::Sprite& sprite, const float deltaTime);
	void playBackwards(sf::Sprite& sprite, const float deltaTime);
	void setFrame(sf::Sprite &sprite, int numberOfFrame);
	void setTimeOfFrameChange(float TimeOfFrameChange);
	void resetTimerOfAnimation();
	int getNumberOfCurrentFrame() const;
	bool wasFrameChanged() const;
protected:
	bool repeated;
	bool numberOfStartRepeatedFrame;
	sf::IntRect startFrame;
	sf::IntRect startRepeatedFrame;
	sf::IntRect currentFrame;
	sf::IntRect endFrame;
	int numberOfCurrentFrame;
	int numberOfFrames;
	bool WasFrameChanged;
	sf::Vector2i sizeOfSingleFrame;
	float timer;
	float timeOfFrameChange;
	bool isOver;
};

