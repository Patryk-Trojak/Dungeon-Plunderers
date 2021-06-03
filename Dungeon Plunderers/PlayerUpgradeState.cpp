#include "pch.h"
#include "PlayerUpgradeState.h"


PlayerUpgradeState::PlayerUpgradeState(StateData& stateData)
	: State(stateData),
	additionalInformationAboutButtons(sf::Vector2f(0, 0), sf::Vector2f(510, 180),
		stateData.resources[TextureID::InformationAboutSaveBackground], stateData.resources.font,
		L"", 30),
	resetUpgradesBought(sf::Vector2f(1690, 950), sf::Vector2f(200, 100),
		stateData.resources[TextureID::GreyButton100x50], stateData.resources.font,
		L"Reset", 40, ContentAlignment::center, 0.f, sf::Color::Red, sf::Color(150, 0, 0)),
	playerData(stateData.savedPlayerData)
{
	initButtons();
	for (auto it = upgradeButtons.begin(); it != upgradeButtons.end(); ++it)
	{
		it->second.setNumberOfUpgradeBought(playerData.numbersOfUpgradeBought[it->first]);
	}
	initTexts();
	initWeaponsSprites();
	initBackgrounds();
}

PlayerUpgradeState::~PlayerUpgradeState()
{
}

void PlayerUpgradeState::update(const float deltaTime)
{
	updateUpgradeButtons(deltaTime);
	resetUpgradesBought.update(mousePositionView);
	if (feedback)
		feedback->update(deltaTime);

	handleShowingAdditionalInformation();
	
	handleDowngrading();
	handleUpgrading();
	handleResetingAllUpgrades();
}

void PlayerUpgradeState::updateInput(const float deltaTime)
{
}

void PlayerUpgradeState::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(background, state);
	drawBackgrounds(target, state);

	drawUpgradeButtons(target, state);
	drawTexts(target, state);
	drawWeapons(target, state);
	target.draw(resetUpgradesBought, state);
	if (drawAdditionalInformation)
		target.draw(additionalInformationAboutButtons, state);
	if (feedback)
		target.draw(*feedback, state);
}

void PlayerUpgradeState::handleSFMLEvent(sf::RenderWindow& window, sf::Event& event)
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
				savePlayerData();
				stateData.states.pop();
			}
		}
	}
}


void PlayerUpgradeState::handleUpgrading()
{
	for (auto i = upgradeButtons.begin(); i != upgradeButtons.end(); ++i)
	{
		if (i->second.wasUpgradeButtonPressed(mousePositionView, wasMousePressed))
		{
			tryBoostUpgrade(i->first);
		}
	}
}


void PlayerUpgradeState::handleDowngrading()
{
	for (auto i = upgradeButtons.begin(); i != upgradeButtons.end(); ++i)
	{
		if (i->second.wasDowngradeButtonPressed(mousePositionView, wasMousePressed))
		{
			tryDecreaseUpgrade(i->first);
		}
	}
}

void PlayerUpgradeState::tryBoostUpgrade(UpgradeName upgradeName)
{
	if (isAbleToBoostUpgrade(upgradeName))
	{
		playerData.numbersOfUpgradeBought.at(upgradeName)++;
		upgradeButtons.at(upgradeName).setNumberOfUpgradeBought(playerData.numbersOfUpgradeBought[upgradeName]);
	}
	else
	{
		makeFeedbackWhyIsNotAbleToBoostUpgrade(upgradeName);
	}
}


void PlayerUpgradeState::tryDecreaseUpgrade(UpgradeName upgradeName)
{
	if (isAbleToDecreaseUpgrade(upgradeName))
	{
		playerData.numbersOfUpgradeBought[upgradeName]--;
		upgradeButtons.at(upgradeName).setNumberOfUpgradeBought(playerData.numbersOfUpgradeBought[upgradeName]);
	}
	else
	{
		makeFeedbackWhyIsNotAbleToDecreaseUpgrade(upgradeName);
	}
}

void PlayerUpgradeState::resetAllUpgrade()
{
	for (auto& i : upgradeButtons)
		i.second.setNumberOfUpgradeBought(0);

	for (auto& i : playerData.numbersOfUpgradeBought)
		i.second = 0;
}

void PlayerUpgradeState::handleResetingAllUpgrades()
{
	if (resetUpgradesBought.wasPressed(mousePositionView, wasMousePressed))
	{
		resetAllUpgrade();
	}
}

void PlayerUpgradeState::setTextOfAdditionalInformation(UpgradeName upgradeName)
{
	switch (upgradeName)
	{
	case UpgradeName::HandgunDamage:
		additionalInformationAboutButtons.setWstring(L"Zwieksza obrazenia zadawane \nprzez jeden pocisk podstawowej \nbroni strzelca");
		break;
	case UpgradeName::HandgunFireRate:
		additionalInformationAboutButtons.setWstring(L"Zwieksza szybkosc strzelania \npodstawowej broni strzelca");
		break;
	case UpgradeName::RifleDamage:
		additionalInformationAboutButtons.setWstring(L"Zwieksza obrazenia zadawane \nprzez jeden pocisk drugiej \nbroni strzelca");
		break;
	case UpgradeName::RifleFireRate:
		additionalInformationAboutButtons.setWstring(L"Zwieksza szybkosc strzelania \ndrugiej broni strzelca");
		break;
	case UpgradeName::RifleInitialAmmo:
		additionalInformationAboutButtons.setWstring(L"Zwieksza poczatkowa ilosc \namunicji drugiej broni strzelca");
		break;
	case UpgradeName::ShotgunDamage:
		additionalInformationAboutButtons.setWstring(L"Zwieksza obrazenia zadawane \nprzez jeden pocisk trzciej \nbroni strzelca");
		break;
	case UpgradeName::ShotgunFireRate:
		additionalInformationAboutButtons.setWstring(L"Zwieksza szybkosc strzelania \ntrzeciej broni strzelca");
		break;
	case UpgradeName::ShotgunInitialAmmo:
		additionalInformationAboutButtons.setWstring(L"Zwieksza poczatkowa ilosc \namunicji trzeciej broni strzelca");
		break;
	case UpgradeName::BasicWandDamage:
		additionalInformationAboutButtons.setWstring(L"Zwieksza obrazenia zadawane \nprzez jeden pocisk podstawowej \nbroni czarodzieja");
		break;
	case UpgradeName::BasicWandFireRate:
		additionalInformationAboutButtons.setWstring(L"Zwieksza szybkosc strzelania \npodstawowej broni czarodzieja");
		break;
	case UpgradeName::FireWandDamage:
		additionalInformationAboutButtons.setWstring(L"Zwieksza obrazenia zadawane \nprzez jeden pocisk drugiej \nbroni czarodzieja");
		break;
	case UpgradeName::FireWandFireRate:
		additionalInformationAboutButtons.setWstring(L"Zwieksza szybkosc strzelania \ndrugiej broni czarodzieja");
		break;
	case UpgradeName::FireWandCostOfShot:
		additionalInformationAboutButtons.setWstring(L"Zmniejsza ilosc pobieranej \nmany przy strzale \nz drugiej broni czarodzieja ");
		break;
	case UpgradeName::IceWandDamage:
		additionalInformationAboutButtons.setWstring(L"Zwieksza obrazenia zadawane \nprzez jeden pocisk trzciej \nbroni czarodzieja");
		break;
	case UpgradeName::IceWandFireRate:
		additionalInformationAboutButtons.setWstring(L"Zwieksza mnoznik zmniejszania \npredkosc przeciwnika po kolizji z \npociskiem trzeciej bronin \nczarodzieja");
		break;
	case UpgradeName::IceWandCostOfShot:
		additionalInformationAboutButtons.setWstring(L"Zmniejsza ilosc pobieranej \nmany przy strzale \nz trzeciej broni czarodzieja ");
		break;
	case UpgradeName::HelicopterDamage:
		additionalInformationAboutButtons.setWstring(L"Zwieksza obrazenia zadawane \nprzez jeden pocisk samolotu \nstrzelca");
		break;
	case UpgradeName::HelicopterFireRate:
		additionalInformationAboutButtons.setWstring(L"Zwieksza szybkosc strzelania \nsamolotu strzelca");
		break;
	case UpgradeName::ShadowWandDamage:
		additionalInformationAboutButtons.setWstring(L"Zwieksza obrazenia zadawane \nprzez jeden pocisk mrocznej \nbroni czarodzieja");
		break;
	case UpgradeName::ShadowWandFireRate:
		additionalInformationAboutButtons.setWstring(L"Zwieksza szybkosc strzelania \nmrocznej broni czarodzieja");
		break;
	}
}

void PlayerUpgradeState::handleShowingAdditionalInformation()
{
	drawAdditionalInformation = false;

	for (auto const& i : upgradeButtons)
	{
		if (i.second.isMouseOver(mousePositionView))
		{
			drawAdditionalInformation = true;
			setTextOfAdditionalInformation(i.first);
			if (i.second.getPosition().y > 800)
			{
				additionalInformationAboutButtons.setPosition(sf::Vector2f(i.second.getPosition().x - 116, i.second.getPosition().y - 230.f));
			}
			else
			{
				additionalInformationAboutButtons.setPosition(sf::Vector2f(i.second.getPosition().x - 116, i.second.getPosition().y + 70.f));
			}
			break;
		}
	}

	if (resetUpgradesBought.isMouseOverButton(mousePositionView))
	{
		drawAdditionalInformation = true;
		additionalInformationAboutButtons.setWstring(L"Resetuje wszyskie kupione ulepszenia. \nZostan¹ zwrócone wszystkie wydane pieni¹dzê");
		additionalInformationAboutButtons.setPosition(sf::Vector2f(resetUpgradesBought.getPosition().x - 520, resetUpgradesBought.getPosition().y));
	}
}

void PlayerUpgradeState::drawUpgradeButtons(sf::RenderTarget& target, sf::RenderStates state) const
{
	for (auto const& i : upgradeButtons)
		target.draw(i.second);
}

void PlayerUpgradeState::updateUpgradeButtons(float deltaTime)
{
	for (auto& i : upgradeButtons)
	{
		i.second.update(mousePositionView);
	}
}

void PlayerUpgradeState::drawTexts(sf::RenderTarget& target, sf::RenderStates state) const
{
	for (auto const& i : texts)
		target.draw(i, state);
}

void PlayerUpgradeState::initTexts()
{
	texts[0].setString(L"Obra¿enia");
	texts[1].setString(L"Szybkostrzelnoœæ");
	texts[2].setString(L"Pocz¹tkowa amunicja");
	texts[3].setString(L"Mniejszy koszt zaklêcia");

	for (auto& i : texts)
	{
		i.setFont(stateData.resources.font);
		i.setCharacterSize(45);
		i.setOutlineThickness(3);
		i.setOutlineColor(sf::Color::Black);
		i.setFillColor(sf::Color::White);
	}
	texts[0].setCharacterSize(50);
	texts[1].setCharacterSize(50);

	texts[0].setPosition(sf::Vector2f(380.f, 30.f));
	texts[1].setPosition(sf::Vector2f(840.f, 30.f));
	texts[2].setPosition(sf::Vector2f(1315.f, 150.f));
	texts[3].setPosition(sf::Vector2f(1311.f, 500.f));
}


bool PlayerUpgradeState::isUpgradeMaxed(UpgradeName upgradeName) const
{
	if (playerData.numbersOfUpgradeBought.at(upgradeName) >= 5)
		return true;
	else
		return false;
}

void PlayerUpgradeState::initButtons()
{
	int maxNumberOfUpgrade = 5;
	
	upgradeButtons.insert(std::make_pair(UpgradeName::HandgunDamage, ShopButton(sf::Vector2f(350.f, 130.f), stateData.resources, maxNumberOfUpgrade)));
	upgradeButtons.insert(std::make_pair(UpgradeName::HandgunFireRate, ShopButton(sf::Vector2f(350.f, 130.f) + sf::Vector2f(500.f, 0.f), stateData.resources, maxNumberOfUpgrade)));

	upgradeButtons.insert(std::make_pair(UpgradeName::RifleDamage, ShopButton(sf::Vector2f(350.f, 130.f) + sf::Vector2f(0.f, 100.f), stateData.resources, maxNumberOfUpgrade)));
	upgradeButtons.insert(std::make_pair(UpgradeName::RifleFireRate, ShopButton(sf::Vector2f(350.f, 130.f) + sf::Vector2f(500.f, 100.f), stateData.resources, maxNumberOfUpgrade)));
	upgradeButtons.insert(std::make_pair(UpgradeName::RifleInitialAmmo, ShopButton(sf::Vector2f(350.f, 130.f) + sf::Vector2f(1000.f, 100.f), stateData.resources, maxNumberOfUpgrade)));


	upgradeButtons.insert(std::make_pair(UpgradeName::ShotgunDamage, ShopButton(sf::Vector2f(350.f, 130.f) + sf::Vector2f(0.f, 200.f), stateData.resources, maxNumberOfUpgrade)));
	upgradeButtons.insert(std::make_pair(UpgradeName::ShotgunFireRate, ShopButton(sf::Vector2f(350.f, 130.f) + sf::Vector2f(500.f, 200.f), stateData.resources, maxNumberOfUpgrade)));
	upgradeButtons.insert(std::make_pair(UpgradeName::ShotgunInitialAmmo, ShopButton(sf::Vector2f(350.f, 130.f) + sf::Vector2f(1000.f, 200.f), stateData.resources, maxNumberOfUpgrade)));

	upgradeButtons.insert(std::make_pair(UpgradeName::BasicWandDamage, ShopButton(sf::Vector2f(350.f, 130.f) + sf::Vector2f(0.f, 350.f), stateData.resources, maxNumberOfUpgrade)));
	upgradeButtons.insert(std::make_pair(UpgradeName::BasicWandFireRate, ShopButton(sf::Vector2f(350.f, 130.f) + sf::Vector2f(500.f, 350.f), stateData.resources, maxNumberOfUpgrade)));

	upgradeButtons.insert(std::make_pair(UpgradeName::FireWandDamage, ShopButton(sf::Vector2f(350.f, 130.f) + sf::Vector2f(0.f, 450.f), stateData.resources, maxNumberOfUpgrade)));
	upgradeButtons.insert(std::make_pair(UpgradeName::FireWandFireRate, ShopButton(sf::Vector2f(350.f, 130.f) + sf::Vector2f(500.f, 450.f), stateData.resources, maxNumberOfUpgrade)));
	upgradeButtons.insert(std::make_pair(UpgradeName::FireWandCostOfShot, ShopButton(sf::Vector2f(350.f, 130.f) + sf::Vector2f(1000.f, 450.f), stateData.resources, maxNumberOfUpgrade)));

	upgradeButtons.insert(std::make_pair(UpgradeName::IceWandDamage, ShopButton(sf::Vector2f(350.f, 130.f) + sf::Vector2f(0.f, 550.f), stateData.resources, maxNumberOfUpgrade)));
	upgradeButtons.insert(std::make_pair(UpgradeName::IceWandFireRate, ShopButton(sf::Vector2f(350.f, 130.f) + sf::Vector2f(500.f, 550.f), stateData.resources, maxNumberOfUpgrade)));
	upgradeButtons.insert(std::make_pair(UpgradeName::IceWandCostOfShot, ShopButton(sf::Vector2f(350.f, 130.f) + sf::Vector2f(1000.f, 550.f), stateData.resources, maxNumberOfUpgrade)));

	upgradeButtons.insert(std::make_pair(UpgradeName::HelicopterDamage, ShopButton(sf::Vector2f(350.f, 130.f) + sf::Vector2f(0.f, 700.f), stateData.resources, maxNumberOfUpgrade)));
	upgradeButtons.insert(std::make_pair(UpgradeName::HelicopterFireRate, ShopButton(sf::Vector2f(350.f, 130.f) + sf::Vector2f(500.f, 700.f), stateData.resources, maxNumberOfUpgrade)));

	upgradeButtons.insert(std::make_pair(UpgradeName::ShadowWandDamage, ShopButton(sf::Vector2f(350.f, 130.f) + sf::Vector2f(0.f, 800.f), stateData.resources, maxNumberOfUpgrade)));
	upgradeButtons.insert(std::make_pair(UpgradeName::ShadowWandFireRate, ShopButton(sf::Vector2f(350.f, 130.f) + sf::Vector2f(500.f, 800.f), stateData.resources, maxNumberOfUpgrade)));
	
}


void PlayerUpgradeState::drawWeapons(sf::RenderTarget& target, sf::RenderStates state) const
{
	for (auto const& i : weapons)
	{
		target.draw(i, state);
	}

	target.draw(weapons[6], state);
}

void PlayerUpgradeState::initWeaponsSprites()
{
	weapons[0].setTexture(stateData.resources[TextureID::Handgun]);
	weapons[1].setTexture(stateData.resources[TextureID::Rifle]);
	weapons[2].setTexture(stateData.resources[TextureID::Shotgun]);

	weapons[3].setTexture(stateData.resources[TextureID::BasicWand]);
	weapons[4].setTexture(stateData.resources[TextureID::FireWand]);
	weapons[5].setTexture(stateData.resources[TextureID::IceWand]);

	weapons[6].setTexture(stateData.resources[TextureID::Helicopter]);

	weapons[7].setTexture(stateData.resources[TextureID::ShadowWand]);

	for (int i = 0; i < weapons.size(); i++)
	{
		if (i == 3 or i == 4 or i == 5 or i == 7)
			weapons[i].setOrigin(sf::Vector2f(0.f, 114 / 2));
		else if (i == 6)
			weapons[i].setOrigin(sf::Vector2f(13.f, 13.f));
		else
			weapons[i].setOrigin(sf::Vector2f(weapons[i].getTexture()->getSize().x / 2, 0.f));
	}

	weapons[3].setRotation(90.f);
	weapons[4].setRotation(90.f);
	weapons[5].setRotation(90.f);
	weapons[7].setRotation(90.f);

	weapons[0].setScale(1.6, 1.6);
	weapons[1].setScale(0.7, 0.7);
	weapons[2].setScale(1.6, 1.6);

	weapons[3].setScale(1.5, 1.5);
	weapons[4].setScale(1.5, 1.5);
	weapons[5].setScale(1.5, 1.5);
	weapons[6].setScale(2.0f, 2.0f);
	weapons[7].setScale(1.5, 1.5);

	weapons[3].setTextureRect(sf::IntRect(0, 5, 50, 114));
	weapons[6].setTextureRect(sf::IntRect(2539, 0, 48, 27));
	weapons[7].setTextureRect(sf::IntRect(0, 0, 46, 114));


	float positionXOfAllWeapons = 200;
	weapons[0].setPosition(sf::Vector2f(positionXOfAllWeapons, 120));
	weapons[1].setPosition(sf::Vector2f(positionXOfAllWeapons, 220));
	weapons[2].setPosition(sf::Vector2f(positionXOfAllWeapons, 320));

	weapons[3].setPosition(sf::Vector2f(positionXOfAllWeapons, 465));
	weapons[4].setPosition(sf::Vector2f(positionXOfAllWeapons, 565));
	weapons[5].setPosition(sf::Vector2f(positionXOfAllWeapons, 665));

	weapons[6].setPosition(sf::Vector2f(positionXOfAllWeapons, 845));

	weapons[7].setPosition(sf::Vector2f(positionXOfAllWeapons, 915));
}

void PlayerUpgradeState::initBackgrounds()
{
	
	for (auto& i : backgrounds)
		i.setTexture(stateData.resources[TextureID::ShopBackground]);


	float positionXOfAllWeapons = 200;

	for (auto& i : backgrounds)
		i.setPosition(40, 200);
}

void PlayerUpgradeState::drawBackgrounds(sf::RenderTarget& target, sf::RenderStates state) const
{
	for (auto const& i : backgrounds)
		target.draw(i);
}

bool PlayerUpgradeState::isAbleToBoostUpgrade(UpgradeName upgradeName) const
{
	if (!isUpgradeMaxed(upgradeName))
		return true;
	else
		return false;
}

bool PlayerUpgradeState::isAbleToDecreaseUpgrade(UpgradeName upgradeName) const
{
	if (playerData.numbersOfUpgradeBought.at(upgradeName) > 0)
		return true;
	else
		return false;
}

void PlayerUpgradeState::makeFeedbackWhyIsNotAbleToBoostUpgrade(UpgradeName upgradeName)
{
	if (isUpgradeMaxed(upgradeName))
		feedback = std::make_unique<Feedback>(sf::Vector2f(200, 700), L"Kupiono ju¿ maksymaln¹ iloœæ tego ulepszenia", 30, stateData.resources.font);
}

void PlayerUpgradeState::makeFeedbackWhyIsNotAbleToDecreaseUpgrade(UpgradeName upgradeName)
{
	if(playerData.numbersOfUpgradeBought[upgradeName] <= 0)
		feedback = std::make_unique<Feedback>(sf::Vector2f(200, 700), L"Nie mo¿na bardziej zmniejszyæ tego ulepszenia!", 30, stateData.resources.font);
}
