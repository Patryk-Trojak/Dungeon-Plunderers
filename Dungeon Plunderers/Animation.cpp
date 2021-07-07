#include "pch.h"
#include "Animation.h"



Animation::Animation(const int StartFrameX, const int StartFrameY, const sf::Vector2i& SizeOfSingleFrame, const int NumberOfFrames, float TimeOfFrameChange, bool repeated, const int StartRepeatedFrame)
	:currentFrame((StartFrameX - 1) * SizeOfSingleFrame.x, (StartFrameY - 1) * SizeOfSingleFrame.y, SizeOfSingleFrame.x, SizeOfSingleFrame.y),
	startRepeatedFrame((StartRepeatedFrame - 1)* SizeOfSingleFrame.x, (StartFrameY - 1)* SizeOfSingleFrame.y, SizeOfSingleFrame.x, SizeOfSingleFrame.y),
	endFrame((NumberOfFrames - 1) * SizeOfSingleFrame.x, (StartFrameY - 1) * SizeOfSingleFrame.y, SizeOfSingleFrame.x, SizeOfSingleFrame.y),
	timeOfFrameChange(TimeOfFrameChange),
	timer(0),
	sizeOfSingleFrame(SizeOfSingleFrame),
	isOver(false),
	WasFrameChanged(false),
	numberOfFrames(NumberOfFrames),
	repeated(repeated),
	numberOfStartRepeatedFrame(StartRepeatedFrame)
{
	numberOfCurrentFrame = StartFrameX;
	numberOfStartRepeatedFrame = StartFrameX;
	startFrame = currentFrame;
}


Animation::Animation()
	:startRepeatedFrame(0, 0, 0, 0),
	currentFrame(0, 0, 0, 0),
	endFrame(0, 0, 0, 0),
	startFrame(0, 0, 0, 0),
	timeOfFrameChange(0),
	timer(0),
	sizeOfSingleFrame(0, 0),
	isOver(false),
	WasFrameChanged(false),
	numberOfFrames(0),
	repeated(true),
	numberOfStartRepeatedFrame(0)
{
	numberOfCurrentFrame = 0;
}

Animation::~Animation()
{
}

void Animation::play(sf::Sprite& sprite, const float deltaTime)
{
	timer += deltaTime;
	WasFrameChanged = false;
	while (timer >= timeOfFrameChange)
	{
		timer = timer - timeOfFrameChange;
		if (currentFrame == endFrame)
		{
			if (repeated)
			{
				currentFrame = startRepeatedFrame;
				numberOfCurrentFrame = numberOfStartRepeatedFrame;
			}
			isOver = true;
		}
		else
		{
			currentFrame.left += sizeOfSingleFrame.x;
			numberOfCurrentFrame++;
		}
		sprite.setTextureRect(currentFrame);
		timer = 0;
		WasFrameChanged = true;
	}
}

void Animation::playBackwards(sf::Sprite& sprite, const float deltaTime)
{
	timer += deltaTime;
	WasFrameChanged = false;
	while (timer >= timeOfFrameChange)
	{
		timer = timer - timeOfFrameChange;
		if (currentFrame == startFrame)
		{
			if (repeated)
			{
				currentFrame = endFrame;
				numberOfCurrentFrame = numberOfFrames;
			}
			isOver = true;
		}
		else
		{
			currentFrame.left -= sizeOfSingleFrame.x;
			numberOfCurrentFrame--;
		}
		sprite.setTextureRect(currentFrame);
		timer = 0;
		WasFrameChanged = true;
	}
}

void Animation::setFrame(sf::Sprite& sprite, int numberOfFrame)
{
	if (numberOfFrame > this->numberOfFrames)
		numberOfFrame = numberOfFrames;
	
	if (numberOfFrame < 1)
		numberOfFrame = 1;

	if(numberOfFrame != numberOfCurrentFrame)
		WasFrameChanged = true;
	else
		WasFrameChanged = false;

	numberOfCurrentFrame = numberOfFrame;

	currentFrame = startFrame;
	currentFrame.left += sizeOfSingleFrame.x * (numberOfFrame - 1);
	sprite.setTextureRect(currentFrame);
	timer = 0;
}

void Animation::setTimeOfFrameChange(float TimeOfFrameChange)
{
	timeOfFrameChange = TimeOfFrameChange;
}

void Animation::setNumberOfFrames(int numberOfFrames)
{
	this->numberOfFrames = numberOfFrames;
	endFrame.left = (numberOfFrames - 1) * endFrame.width;
}

void Animation::resetTimerOfAnimation()
{
	timer = 0.f;
}

int Animation::getNumberOfCurrentFrame() const
{
	return numberOfCurrentFrame;
}

bool Animation::wasFrameChanged() const
{
	return WasFrameChanged;
}
