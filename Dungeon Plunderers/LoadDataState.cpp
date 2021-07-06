#include "pch.h"
#include "LoadDataState.h"

LoadDataState::LoadDataState(StateData& stateData)
	:State(stateData)
{
}

LoadDataState::~LoadDataState()
{
}

void LoadDataState::handleSFMLEvent(sf::RenderWindow& window, sf::Event& event)
{
}

void LoadDataState::update(const float deltaTime)
{
	loadAllTextures();
	loadKeybinds();
	loadSettings();
	stateData.resources.font.loadFromFile("orange kid.ttf");
}

void LoadDataState::loadAllTextures()
{
	stateData.resources.textures.add(TextureID::Crosshair, loadTexture(".\\Textures\\Crosshair.png"));
	stateData.resources.textures.add(TextureID::Cursor, loadTexture(".\\Textures\\Cursor.png"));
	stateData.resources.textures.add(TextureID::RifleAmmoBox, loadTexture(".\\Textures\\RifleAmmoBox.png"));
	stateData.resources.textures.add(TextureID::AmmoForShutgunBonus, loadTexture(".\\Textures\\AmmoForShutgunBonus.png"));
	stateData.resources.textures.add(TextureID::BackgroundGame, loadTexture(".\\Textures\\pavement.png", true));
	stateData.resources.textures.add(TextureID::ToolbarBackground, loadTexture(".\\Textures\\ToolbarBackground.png", true));
	stateData.resources.textures.add(TextureID::Portal, loadTexture(".\\Textures\\Portal.png"));
	stateData.resources.textures.add(TextureID::Warning, loadTexture(".\\Textures\\Warning.png"));

	stateData.resources.textures.add(TextureID::PotionBar, loadTexture(".\\Textures\\PotionBar.png"));
	stateData.resources.textures.add(TextureID::Blood1, loadTexture(".\\Textures\\Blood1.png"));
	stateData.resources.textures.add(TextureID::Blood2, loadTexture(".\\Textures\\Blood2.png"));
	stateData.resources.textures.add(TextureID::Blood3, loadTexture(".\\Textures\\Blood3.png"));
	stateData.resources.textures.add(TextureID::Blood4, loadTexture(".\\Textures\\Blood4.png"));
	stateData.resources.textures.add(TextureID::Blood5, loadTexture(".\\Textures\\Blood5.png"));
	stateData.resources.textures.add(TextureID::SnowDust, loadTexture(".\\Textures\\SnowDust.png"));
	stateData.resources.textures.add(TextureID::FireExplosion, loadTexture(".\\Textures\\FireExplosion.png"));
	stateData.resources.textures.add(TextureID::Fire, loadTexture(".\\Textures\\Fire.png"));

	//blocks
	stateData.resources.textures.add(TextureID::Brick, loadTexture(".\\Textures\\Blocks.png", true, sf::IntRect(0, 0, 50, 50)));
	stateData.resources.textures.add(TextureID::Dirt, loadTexture(".\\Textures\\Blocks.png", true, sf::IntRect(50, 0, 50, 50)));
	stateData.resources.textures.add(TextureID::Concrate, loadTexture(".\\Textures\\Blocks.png", true, sf::IntRect(100, 0, 50, 50)));
	stateData.resources.textures.add(TextureID::Granite, loadTexture(".\\Textures\\Blocks.png", true, sf::IntRect(150, 0, 50, 50)));
	stateData.resources.textures.add(TextureID::Blocks, loadTexture(".\\Textures\\Blocks.png"));

	stateData.resources.textures.add(TextureID::Trampoline, loadTexture(".\\Textures\\Trampoline.png"));

	stateData.resources.textures.add(TextureID::CppLogo, loadTexture(".\\Textures\\C++Logo.png"));
	stateData.resources.textures.add(TextureID::Coin, loadTexture(".\\Textures\\Coin.png"));
	stateData.resources.textures.add(TextureID::Cloud, loadTexture(".\\Textures\\Cloud.png"));
	stateData.resources.textures.add(TextureID::MagicShield, loadTexture(".\\Textures\\MagicShield.png"));

	stateData.resources.textures.add(TextureID::HealthPotion, loadTexture(".\\Textures\\HealthPotion.png"));
	stateData.resources.textures.add(TextureID::ManaPotion, loadTexture(".\\Textures\\ManaPotion.png"));
	stateData.resources.textures.add(TextureID::Helicopter, loadTexture(".\\Textures\\Helicopter.png"));
	stateData.resources.textures.add(TextureID::SFMLLogo, loadTexture(".\\Textures\\SFMLLogo.png"));
	stateData.resources.textures.add(TextureID::Stormtrooper, loadTexture(".\\Textures\\Stormtrooper.png"));

	stateData.resources.textures.add(TextureID::PlayerHealthBarBackground, loadTexture(".\\Textures\\PlayerHealthBar.png", true, sf::IntRect(0, 0, 225, 54)));
	stateData.resources.textures.add(TextureID::PlayerHealthBarHealth, loadTexture(".\\Textures\\PlayerHealthBar.png", true, sf::IntRect(225, 0, 165, 48)));
	stateData.resources.textures.add(TextureID::ShieldHealthBarBackground, loadTexture(".\\Textures\\ShieldHealthBar.png", true, sf::IntRect(0, 0, 113, 32)));
	stateData.resources.textures.add(TextureID::ShieldHealthBar, loadTexture(".\\Textures\\ShieldHealthBar.png", true, sf::IntRect(113, 0, 78, 27)));
	stateData.resources.textures.add(TextureID::ManaBarBackground, loadTexture(".\\Textures\\ManaBar.png", true, sf::IntRect(0, 0, 225, 54)));
	stateData.resources.textures.add(TextureID::ManaBarMana, loadTexture(".\\Textures\\ManaBar.png", true, sf::IntRect(225, 0, 168, 48)));
	stateData.resources.textures.add(TextureID::EnemyHealthBarBackground, loadTexture(".\\Textures\\EnemyHealthBar.png", false, sf::IntRect(0, 0, 110, 26)));
	stateData.resources.textures.add(TextureID::EnemyHealthBarHealth, loadTexture(".\\Textures\\EnemyHealthBar.png", false, sf::IntRect(110, 0, 108, 24)));
	stateData.resources.textures.add(TextureID::LevelBarBackground, loadTexture(".\\Textures\\LevelBar.png", false, sf::IntRect(0, 0, 225, 54)));
	stateData.resources.textures.add(TextureID::LevelBarLevel, loadTexture(".\\Textures\\LevelBar.png", false, sf::IntRect(225, 0, 153, 48)));
	stateData.resources.textures.add(TextureID::Wizard, loadTexture(".\\Textures\\Wizard.png"));
	stateData.resources.textures.add(TextureID::ShadowWizard, loadTexture(".\\Textures\\ShadowWizard.png"));

	//Enemies
	stateData.resources.textures.add(TextureID::DeadlyFlower, loadTexture(".\\Textures\\DeadlyFlower.png"));
	stateData.resources.textures.add(TextureID::Fly, loadTexture(".\\Textures\\Fly.png"));
	stateData.resources.textures.add(TextureID::Skeleton2, loadTexture(".\\Textures\\Skeleton.png"));
	stateData.resources.textures.add(TextureID::ZombieGirl, loadTexture(".\\Textures\\ZombieGirl.png"));
	stateData.resources.textures.add(TextureID::GunEnemy, loadTexture(".\\Textures\\GunEnemy.png"));
	stateData.resources.textures.add(TextureID::Spikes, loadTexture(".\\Textures\\Spikes.png"));
	stateData.resources.textures.add(TextureID::Slime, loadTexture(".\\Textures\\Slime.png"));
	stateData.resources.textures.add(TextureID::ZombieInGround, loadTexture(".\\Textures\\ZombieInGround.png"));
	stateData.resources.textures.add(TextureID::Ghost, loadTexture(".\\Textures\\Ghost.png"));
	stateData.resources.textures.add(TextureID::Bat, loadTexture(".\\Textures\\Bat.png"));
	stateData.resources.textures.add(TextureID::SpinningSpikes, loadTexture(".\\Textures\\SpinningSpikes.png"));

	//Projectiles
	stateData.resources.textures.add(TextureID::Bullet, loadTexture(".\\Textures\\Bullet.png"));
	stateData.resources.textures.add(TextureID::Electroball, loadTexture(".\\Textures\\ElectroBall.png"));
	stateData.resources.textures.add(TextureID::Fireball, loadTexture(".\\Textures\\Fireball.png"));
	stateData.resources.textures.add(TextureID::Icicle, loadTexture(".\\Textures\\Icicle.png"));
	stateData.resources.textures.add(TextureID::ShadowBall, loadTexture(".\\Textures\\ShadowBall.png"));
	stateData.resources.textures.add(TextureID::RockProjectile, loadTexture(".\\Textures\\RockProjectile.png"));
	stateData.resources.textures.add(TextureID::SlimeProjectile, loadTexture(".\\Textures\\SlimeProjectile.png"));
	stateData.resources.textures.add(TextureID::ProjectileOfDeadlyFlower, loadTexture(".\\Textures\\ProjectileOfDeadlyFlower.png"));
	stateData.resources.textures.add(TextureID::ProjectileOfBoss, loadTexture(".\\Textures\\ProjectileOfBoss.png"));
	stateData.resources.textures.add(TextureID::ProjectileOfBoss2, loadTexture(".\\Textures\\ProjectileOfBoss2.png"));
	stateData.resources.textures.add(TextureID::Laser, loadTexture(".\\Textures\\Laser.png", true));
	//Weapons
	stateData.resources.textures.add(TextureID::Handgun, loadTexture(".\\Textures\\Handgun.png"));
	stateData.resources.textures.add(TextureID::Rifle, loadTexture(".\\Textures\\Rifle.png"));
	stateData.resources.textures.add(TextureID::Shotgun, loadTexture(".\\Textures\\Shotgun.png"));
	stateData.resources.textures.add(TextureID::BasicWand, loadTexture(".\\Textures\\BasicWand.png"));
	stateData.resources.textures.add(TextureID::FireWand, loadTexture(".\\Textures\\FireWand.png"));
	stateData.resources.textures.add(TextureID::IceWand, loadTexture(".\\Textures\\IceWand.png"));
	stateData.resources.textures.add(TextureID::ShadowWand, loadTexture(".\\Textures\\ShadowWand.png"));

	//Buttons
	stateData.resources.textures.add(TextureID::GreyButton100x50, loadTexture(".\\Textures\\GreyButton100x50.png"));
	stateData.resources.textures.add(TextureID::GreyButton200x150, loadTexture(".\\Textures\\GreyButton200x150.png"));
	stateData.resources.textures.add(TextureID::GreyButton300x70, loadTexture(".\\Textures\\GreyButton300x70.png"));
	stateData.resources.textures.add(TextureID::GreyButton750x86, loadTexture(".\\Textures\\GreyButton750x86.png"));
	stateData.resources.textures.add(TextureID::BackButton, loadTexture(".\\Textures\\BackButton.png"));
	stateData.resources.textures.add(TextureID::DeleteSaveButton, loadTexture(".\\Textures\\DeleteSaveButton.png"));
	stateData.resources.textures.add(TextureID::Plus, loadTexture(".\\Textures\\Plus.png"));
	stateData.resources.textures.add(TextureID::Minus, loadTexture(".\\Textures\\Minus.png"));
	stateData.resources.textures.add(TextureID::Arrow, loadTexture(".\\Textures\\Arrow.png"));
	stateData.resources.textures.add(TextureID::SliderButton, loadTexture(".\\Textures\\SliderButton.png"));
	stateData.resources.textures.add(TextureID::Slider, loadTexture(".\\Textures\\Slider.png"));
	stateData.resources.textures.add(TextureID::Axis, loadTexture(".\\Textures\\Axis.png"));
	stateData.resources.textures.add(TextureID::MachinegunButton, loadTexture(".\\Textures\\MachinegunButton.png"));
	stateData.resources.textures.add(TextureID::Checbox50x50, loadTexture(".\\Textures\\Checbox50x50.png"));
	stateData.resources.textures.add(TextureID::MessageboxBackground, loadTexture(".\\Textures\\MessageboxBackground.png"));
	stateData.resources.textures.add(TextureID::RedButton750x86, loadTexture(".\\Textures\\RedButton750x86.png"));
	stateData.resources.textures.add(TextureID::SaveButton, loadTexture(".\\Textures\\SaveButton.png"));
	stateData.resources.textures.add(TextureID::DarkRedButton750x86, loadTexture(".\\Textures\\DarkRedButton750x86.png"));
	stateData.resources.textures.add(TextureID::TextboxBackground, loadTexture(".\\Textures\\Textbox.png"));
	stateData.resources.textures.add(TextureID::Searcher, loadTexture(".\\Textures\\Searcher.png"));
	stateData.resources.textures.add(TextureID::SearchBox, loadTexture(".\\Textures\\SearchBox.png"));
	stateData.resources.textures.add(TextureID::SkipButton, loadTexture(".\\Textures\\SkipButton.png"));
	stateData.resources.textures.add(TextureID::AcceptButton, loadTexture(".\\Textures\\AcceptButton.png"));
	stateData.resources.textures.add(TextureID::ScrollerButton, loadTexture(".\\Textures\\ScrollerButton.png"));
	stateData.resources.textures.add(TextureID::Loupe, loadTexture(".\\Textures\\Loupe.png"));
	stateData.resources.textures.add(TextureID::RedButton89x43, loadTexture(".\\Textures\\RedButton89x43.png"));
	stateData.resources.textures.add(TextureID::DeleteButton, loadTexture(".\\Textures\\DeleteButton.png"));
	stateData.resources.textures.add(TextureID::Delete, loadTexture(".\\Textures\\Delete.png"));
	stateData.resources.textures.add(TextureID::InformationAboutSaveBackground, loadTexture(".\\Textures\\InformationAboutSaveBackground.png"));
	stateData.resources.textures.add(TextureID::ShopBackground, loadTexture(".\\Textures\\ShopBackground.png"));
	stateData.resources.textures.add(TextureID::InfinitySymbol, loadTexture(".\\Textures\\InfinitySymbol.png"));	
	stateData.resources.textures.add(TextureID::InfinitySymbol, loadTexture(".\\Textures\\InfinitySymbol.png"));
}

void LoadDataState::loadKeybinds()
{
	stateData.keybinds = PersistenceLoader::loadKeybinds();
}

void LoadDataState::loadSettings()
{
	std::ifstream file;
	file.open(".//Settings//config.txt");
	if (!file.good())
	{
		std::ofstream newFile;
		newFile.open(".//Settings//config.txt");

		newFile << stateData.settings.fullscreen << std::endl;
		newFile << stateData.settings.windowSize.x << std::endl;
		newFile << stateData.settings.windowSize.y << std::endl;
		newFile << stateData.settings.windowPosition.x << std::endl;
		newFile << stateData.settings.windowPosition.y << std::endl;
		newFile << stateData.settings.resizeProportionally << std::endl;
		newFile << stateData.settings.isVerticalSyncEnabled << std::endl;
		newFile << stateData.settings.isLimitFPSEnabled << std::endl;
		newFile << stateData.settings.maxFPS << std::endl;
		newFile << stateData.settings.showFPS << std::endl;
		newFile << stateData.settings.FPSOnTop << std::endl;
		newFile << stateData.settings.FPSOnLeft << std::endl;
		newFile << stateData.settings.characterSizeOfFPS << std::endl;
		newFile << static_cast<int>(stateData.settings.colorOfFPS.r) << std::endl;
		newFile << static_cast<int>(stateData.settings.colorOfFPS.g) << std::endl;
		newFile << static_cast<int>(stateData.settings.colorOfFPS.b) << std::endl;
		newFile << static_cast<int>(stateData.settings.colorOfFPS.a) << std::endl;
		newFile << stateData.settings.showOutlineFPS << std::endl;
		newFile << stateData.settings.outlineThickness << std::endl;
		newFile << static_cast<int>(stateData.settings.colorOfOutlineFPS.r) << std::endl;
		newFile << static_cast<int>(stateData.settings.colorOfOutlineFPS.g) << std::endl;
		newFile << static_cast<int>(stateData.settings.colorOfOutlineFPS.b) << std::endl;
		newFile << static_cast<int>(stateData.settings.colorOfOutlineFPS.a);

		newFile.close();
	}
	else
	{
		if (!file.eof())
		{
			int colorOfFPSR, colorOfFPSG, colorOfFPSB, colorOfFPSA, colorOfOutlineFPSR, colorOfOutlineFPSG, colorOfOutlineFPSB, colorOfOutlineFPSA;
			file >> stateData.settings.fullscreen;
			file >> stateData.settings.windowSize.x;
			file >> stateData.settings.windowSize.y;
			file >> stateData.settings.windowPosition.x;
			file >> stateData.settings.windowPosition.y;
			file >> stateData.settings.resizeProportionally;
			file >> stateData.settings.isVerticalSyncEnabled;
			file >> stateData.settings.isLimitFPSEnabled;
			file >> stateData.settings.maxFPS;
			file >> stateData.settings.showFPS;
			file >> stateData.settings.FPSOnTop;
			file >> stateData.settings.FPSOnLeft;
			file >> stateData.settings.characterSizeOfFPS;
			file >> colorOfFPSR;
			file >> colorOfFPSG;
			file >> colorOfFPSB;
			file >> colorOfFPSA;
			file >> stateData.settings.showOutlineFPS;
			file >> stateData.settings.outlineThickness;
			file >> colorOfOutlineFPSR;
			file >> colorOfOutlineFPSG;
			file >> colorOfOutlineFPSB;
			file >> colorOfOutlineFPSA;

			stateData.settings.colorOfFPS = sf::Color(colorOfFPSR, colorOfFPSG, colorOfFPSB, colorOfFPSA);
			stateData.settings.colorOfOutlineFPS = sf::Color(colorOfOutlineFPSR, colorOfOutlineFPSG, colorOfOutlineFPSB, colorOfOutlineFPSA);
		}
	}
	file.close();
}


void LoadDataState::updateInput(const float deltaTime)
{
}

std::unique_ptr<sf::Texture> LoadDataState::loadTexture(const std::string& filepath, const bool repeated, const sf::IntRect& area)
{
	std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
	texture->loadFromFile(filepath, area);
	texture->setRepeated(repeated);
	return texture;
}

void LoadDataState::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
}
