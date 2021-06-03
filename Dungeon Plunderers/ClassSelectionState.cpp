#include "pch.h"
#include "ClassSelectionState.h"

ClassSelectionState::ClassSelectionState(StateData& stateData)
	: State(stateData), 
	chooseStormtrooper(sf::Vector2f(960 - 250 - 400, 190), sf::Vector2f(400, 700),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"", 40),
	chooseWizard(sf::Vector2f(960 + 250, 190), sf::Vector2f(400, 700),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"", 40)
{

	wizard.setTexture(stateData.resources[TextureID::Wizard]);
	wizard.setTextureRect(sf::IntRect(0, 0, 75, 100));
	wizard.setPosition(chooseWizard.getPosition() + chooseWizard.getSize() / 2.f + sf::Vector2f(- 152 + 160 - 18, -200));
	wizard.setScale(2.f, 2.f);
	wizard.setOrigin(80, 0);
	//304, 499

	stormtrooper.setTexture(stateData.resources[TextureID::Stormtrooper]);
	stormtrooper.setTextureRect(sf::IntRect(0, 0, 117, 207));
	stormtrooper.setScale(2.f, 2.f);
	stormtrooper.setOrigin(62, 0);
	stormtrooper.setPosition(chooseStormtrooper.getPosition() + chooseStormtrooper.getSize() / 2.f + sf::Vector2f(-117 + 124 - 40, -414 / 2));
	//156, 276

	wizardArm.setTexture(stateData.resources[TextureID::Wizard]);
	wizardArm.setTextureRect(sf::IntRect(460, 0, 72, 40));
	wizardArm.setOrigin(9, 15);
	wizardArm.setScale(2.f, 2.f);
	wizardArm.setPosition(wizard.getPosition() + sf::Vector2f(10 * 2, 112 * 2));

	stormtrooperArm.setTexture(stateData.resources[TextureID::Stormtrooper]);
	stormtrooperArm.setTextureRect(sf::IntRect(1053, 0, 87, 23));
	stormtrooperArm.setOrigin(8, 10);
	stormtrooperArm.setScale(2.f, 2.f);
	stormtrooperArm.setPosition(stormtrooper.getPosition() + sf::Vector2f(0, 75.f * 2.f));

	stormtrooperAnimation = Animation(1, 1, sf::Vector2i(117, 207), 9, 0.05f);
	wizardAnimation = Animation(1, 1, sf::Vector2i(152, 200), 3, 0.1f);


	handgun.setTexture(stateData.resources[TextureID::Handgun]);
	handgun.setOrigin(0, 20);
	handgun.setScale(2.f, 2.f);
	handgun.setPosition(sf::Vector2f(stormtrooperArm.getPosition().x + 105 , stormtrooperArm.getPosition().y));

	wand.setTexture(stateData.resources[TextureID::IceWand]);
	wand.setOrigin(30.f, 50.f);
	wand.setScale(2.f, 2.f);
	wand.setPosition(wizardArm.getPosition() + sf::Vector2f(123, 0));


	//temp

	showHitboxes.setPosition(0, 0);
	showHitboxes.setSize(sf::Vector2f(50, 50));
	if (getShowHitboxes())
	{
		showHitboxes.setFillColor(sf::Color::Red);
	}
	else
	{
		showHitboxes.setFillColor(sf::Color::Transparent);
	}

	showHitboxes.setOutlineColor(sf::Color::White);
	showHitboxes.setOutlineThickness(3);
}

ClassSelectionState::~ClassSelectionState()
{
}

void ClassSelectionState::update(const float deltaTime)
{
	chooseStormtrooper.update(mousePositionView);
	chooseWizard.update(mousePositionView);
	if (feedback)
		feedback->update(deltaTime);
	if (chooseStormtrooper.wasPressed(mousePositionView, wasMousePressed))
	{
		stateData.savedPlayerData.isStormtrooperChosen = (true);
		feedback = std::make_unique<Feedback>(sf::Vector2f(0, 700), L"Wybrano strzelca jako domyœln¹ klasê", 50, stateData.resources.font);
	}
	if (chooseWizard.wasPressed(mousePositionView, wasMousePressed))
	{
		stateData.savedPlayerData.isStormtrooperChosen = (false);
		feedback = std::make_unique<Feedback>(sf::Vector2f(0, 700), L"Wybrano czarodzieja jako domyœln¹ klasê", 50, stateData.resources.font);
	}

	if (chooseStormtrooper.isMouseOverButton(mousePositionView))
		stormtrooperAnimation.play(stormtrooper, deltaTime);
	else
		stormtrooperAnimation.setFrame(stormtrooper, 1);

	if (chooseWizard.isMouseOverButton(mousePositionView))
		wizardAnimation.play(wizard, deltaTime);
	else
		wizardAnimation.setFrame(wizard, 1);

	updatePositionWizardArm();
	wand.setPosition(wizardArm.getPosition() + sf::Vector2f(123, 0));
	//temp
	if (showHitboxes.getGlobalBounds().contains(mousePositionView) and wasMousePressed)
	{
		if (getShowHitboxes())
		{
			getShowHitboxes() = false;
			showHitboxes.setFillColor(sf::Color::Transparent);

		}
		else
		{
			getShowHitboxes() = true;
			showHitboxes.setFillColor(sf::Color::Red);

		}
	}
}

void ClassSelectionState::handleSFMLEvent(sf::RenderWindow& window, sf::Event& event)
{
	wasMousePressed = false;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		resizeWindowProportionally(window, event);

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				wasMousePressed = true;
			}
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PersistenceSaver::save(stateData.savedPlayerData, stateData.nameOfCurrentlyLoadedPlayerSave);

				stateData.states.pop();
			}
		}
	}
}

void ClassSelectionState::updateInput(const float deltaTime)
{
}

void ClassSelectionState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(chooseStormtrooper, states);
	target.draw(chooseWizard, states);
	target.draw(wizard, states);
	target.draw(stormtrooper, states);	

	target.draw(handgun, states);
	target.draw(wand, states);

	target.draw(wizardArm, states);
	target.draw(stormtrooperArm, states);

	

	if(feedback)
		target.draw(*feedback, states);
}

void ClassSelectionState::updatePositionWizardArm()
{
	switch (wizardAnimation.getNumberOfCurrentFrame())
	{
	case 1:
		wizardArm.setPosition(wizard.getPosition() + sf::Vector2f(20, 224));
		break;
	case 2:
		wizardArm.setPosition(wizard.getPosition() + sf::Vector2f(20, 224 - 8));
		break;
	case 3:
		wizardArm.setPosition(wizard.getPosition() + sf::Vector2f(20 + 8, 224 - 8));
		break;
	}
}
