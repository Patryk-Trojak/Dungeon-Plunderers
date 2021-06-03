#include "pch.h"
#include "ShopState.h"

ShopState::ShopState(StateData& stateData)
	: PlayerUpgradeState(stateData),
	moneyHUD(sf::Vector2f(1700.f, 850.f), stateData.resources, stateData.savedPlayerData.money),
	weaponOfHelicopter(sf::Vector2f(200, 845), sf::Vector2f(-50.f, -50.f), stateData.resources[TextureID::Bullet], 0.08f, 2)
{
	for (auto it = upgradeButtons.begin(); it != upgradeButtons.end(); ++it)
	{
		it->second.setNumberOfUpgradeBought(playerData.numbersOfUpgradeBought[it->first]);
		it->second.setPrice(makePriceOfUpgrade(playerData.numbersOfUpgradeBought[it->first]));
	}
	initWeaponsSprites();
}

ShopState::~ShopState()
{
}


void ShopState::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(background, state);

	drawBackgrounds(target, state);
	for (auto const& i : projectiles)
		target.draw(*i);

	drawUpgradeButtons(target, state);
	drawTexts(target, state);
	drawWeapons(target, state);
	target.draw(resetUpgradesBought, state);
	if (drawAdditionalInformation)
		target.draw(additionalInformationAboutButtons, state);
	if (feedback)
		target.draw(*feedback, state);

	target.draw(weaponOfHelicopter, state);

	drawWeapons(target, state);

	target.draw(moneyHUD, state);
}

void ShopState::update(const float deltaTime)
{
	PlayerUpgradeState::update(deltaTime);
	handleShooting(deltaTime);
}


void ShopState::handleShooting(float deltaTime)
{
	updateRotationWeapon();
	weaponOfHelicopter.setPosition(sf::Vector2f(weapons[6].getPosition().x + cos((weapons[6].getRotation()) * M_PI / 180) * (87 + weaponOfHelicopter.getOffset().x), weapons[6].getPosition().y + sin((weapons[6].getRotation()) * M_PI / 180) * (87 + weaponOfHelicopter.getOffset().x)));
	weaponOfHelicopter.updateTimerOfShooting(deltaTime);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		weaponOfHelicopter.attack(projectiles, mousePositionView);
	}

	for (auto& i : projectiles)
		i->update(deltaTime);

	eraseProjectiles();
}

void ShopState::updateRotationWeapon()
{
	sf::Vector2f distanceBetweenMouseAndArm = weapons[6].getPosition() - mousePositionView;
	float distance = sqrt(pow(distanceBetweenMouseAndArm.x, 2) + pow(distanceBetweenMouseAndArm.y, 2));
	float angle = (asin(distanceBetweenMouseAndArm.y / distance) * 180.0) / M_PI;

	if (mousePositionView.x > weapons[6].getPosition().x)
	{
		weaponOfHelicopter.setRotation(-angle);
		weapons[6].setRotation(-angle);
	}
	else
	{
		weaponOfHelicopter.setRotation(-180 + angle);
		weapons[6].setRotation(-180 + angle);
	}
}

void ShopState::eraseProjectiles()
{
	for (size_t i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i]->getPosition().x < 0 or projectiles[i]->getPosition().x > 2000
			or projectiles[i]->getPosition().y < 0 or projectiles[i]->getPosition().y > 1200)
		{
			projectiles.erase(projectiles.begin() + i);
		}
	}

}

void ShopState::savePlayerData()
{
	PersistenceSaver::save(playerData, stateData.nameOfCurrentlyLoadedPlayerSave);
}

void ShopState::tryBoostUpgrade(UpgradeName upgradeName)
{
	if (isAbleToBoostUpgrade(upgradeName))
	{
		playerData.numbersOfUpgradeBought.at(upgradeName)++;
		playerData.money -= upgradeButtons.at(upgradeName).getPrice();
		playerData.spentMoneyInShop += upgradeButtons.at(upgradeName).getPrice();

		upgradeButtons.at(upgradeName).setNumberOfUpgradeBought(playerData.numbersOfUpgradeBought[upgradeName]);
		upgradeButtons.at(upgradeName).setPrice( makePriceOfUpgrade(playerData.numbersOfUpgradeBought.at(upgradeName)) );
		moneyHUD.setMoney(playerData.money);
	}
	else
	{
		makeFeedbackWhyIsNotAbleToBoostUpgrade(upgradeName);
	}
}

void ShopState::tryDecreaseUpgrade(UpgradeName upgradeName)
{
	if (isAbleToDecreaseUpgrade(upgradeName))
	{
		playerData.numbersOfUpgradeBought.at(upgradeName)--;
		upgradeButtons.at(upgradeName).setNumberOfUpgradeBought(playerData.numbersOfUpgradeBought[upgradeName]);
		upgradeButtons.at(upgradeName).setPrice(makePriceOfUpgrade(playerData.numbersOfUpgradeBought.at(upgradeName)));

		playerData.money += upgradeButtons.at(upgradeName).getPrice();
		playerData.spentMoneyInShop -= upgradeButtons.at(upgradeName).getPrice();	
		moneyHUD.setMoney(playerData.money);
	}
	else
	{
		makeFeedbackWhyIsNotAbleToDecreaseUpgrade(upgradeName);
	}
}

void ShopState::makeFeedbackWhyIsNotAbleToBoostUpgrade(UpgradeName upgradeName)
{
	if(!hasEnoughMoneyToBuyUpgrade(upgradeName))
		feedback = std::make_unique<Feedback>(sf::Vector2f(200, 700), L"Nie masz wystarczajaco pieniêdzy", 30, stateData.resources.font);

	if(isUpgradeMaxed(upgradeName))
		feedback = std::make_unique<Feedback>(sf::Vector2f(200, 700), L"Nie mo¿na bardziej wymaksowac tego ulepszenia!", 30, stateData.resources.font);
}

void ShopState::resetAllUpgrade()
{
	PlayerUpgradeState::resetAllUpgrade();
	playerData.money += playerData.spentMoneyInShop;
	playerData.spentMoneyInShop = 0;
	moneyHUD.setMoney(playerData.money);
}

bool ShopState::isAbleToBoostUpgrade(UpgradeName upgradeName) const
{
	if (hasEnoughMoneyToBuyUpgrade(upgradeName) and !isUpgradeMaxed(upgradeName))
		return true;
	
	return false;
}

bool ShopState::hasEnoughMoneyToBuyUpgrade(UpgradeName upgradeName) const
{
	if (upgradeButtons.at(upgradeName).getPrice() <= playerData.money)
		return true;
	
	return false;
}

int ShopState::makePriceOfUpgrade(int numberOfUpgrade)
{
	return numberOfUpgrade * 1500 + 500;
}
