#pragma once
#include "PlayerData.h"

struct PlayerStats {
	int health = 0;
};

struct StormtrooperStats
	:public PlayerStats
{
	int handgunDamage = 0;
	int rifleDamage = 0;
	int shotgunDamage = 0;
	
	int handgunFireRate = 0;
	int rifleFireRate = 0;
	int shotgunFireRate = 0;
	
	int rifleInitialAmmo = 0;
	int shotgunInitialAmmo = 0;
};

struct WizardStats
	:public PlayerStats
{
	int basicWandDamage = 0;
	int fireWandDamage = 0;
	int iceWandDamage = 0;

	int basicWandFireRate = 0;
	int fireWandFireRate = 0;
	int iceWandFireRate = 0;

	int fireWandCostOfShot = 0;
	int iceWandCostOfShot = 0;
};

struct HelicopterStats
	:public PlayerStats
{
	int damage = 0;
	int fireRate = 0;
};

struct WizardOnCloudStats
	:public PlayerStats
{
	int damage = 0;
	int fireRate = 0;
	int cloudHealth = 0;
	int shieldHealth = 0;
};

class StatsPlayerCreator
{
public:
	static StormtrooperStats stormtrooperStats(const PlayerData& playerSave);
	static WizardStats wizardStats(const PlayerData& playerSave);
	static HelicopterStats helicopterStats(const PlayerData& playerSave);
	static WizardOnCloudStats wizardOnCloudStats(const PlayerData& playerSave);
	static int getExpierienceToNextLevel(int numberOfOPlayerLevel);
};



/*	switch (selectedButton - ShopButtons.begin())
	{
	case 0:
		stateData.savedPlayerData.setDamageOfProjectile(Projectiles::HandgunBullet, stateData.savedPlayerData.getDamageOfProjectiles().at(Projectiles::HandgunBullet) + 5);
		break;
	case 1:
		stateData.savedPlayerData.setFireRateOfWeapon(Weapons::Handgun, stateData.savedPlayerData.getFireRateOfWeapons().at(Weapons::Handgun) - 0.1f);
		break;
	case 2:
		stateData.savedPlayerData.setDamageOfProjectile(Projectiles::MachingunBullet, stateData.savedPlayerData.getDamageOfProjectiles().at(Projectiles::MachingunBullet) + 5);
		break;
	case 3:
		stateData.savedPlayerData.setFireRateOfWeapon(Weapons::Machingun, stateData.savedPlayerData.getFireRateOfWeapons().at(Weapons::Machingun) - 0.1f);
		break;
	case 4:
		stateData.savedPlayerData.setInitiallyAmmoOfMachingun(stateData.savedPlayerData.getInitiallyAmmoOfMachingun() + 10);
		break;
	case 5:
		stateData.savedPlayerData.setDamageOfProjectile(Projectiles::ShotgunBullet, stateData.savedPlayerData.getDamageOfProjectiles().at(Projectiles::ShotgunBullet) + 5);
		break;
	case 6:
		stateData.savedPlayerData.setFireRateOfWeapon(Weapons::Shotgun, stateData.savedPlayerData.getFireRateOfWeapons().at(Weapons::Shotgun) - 0.2f);
		break;
	case 7:
		stateData.savedPlayerData.setInitiallyAmmoOfShotgun(stateData.savedPlayerData.getInitiallyAmmoOfShotgun() + 5);
		break;
	case 8:
		stateData.savedPlayerData.setDamageOfProjectile(Projectiles::BasicWandProjectile, stateData.savedPlayerData.getDamageOfProjectiles().at(Projectiles::BasicWandProjectile) + 5);
		break;
	case 9:
		stateData.savedPlayerData.setFireRateOfWeapon(Weapons::BasicWand, stateData.savedPlayerData.getFireRateOfWeapons().at(Weapons::BasicWand) - 0.1f);
		break;
	case 10:
		stateData.savedPlayerData.setDamageOfProjectile(Projectiles::FireWandProjectile, stateData.savedPlayerData.getDamageOfProjectiles().at(Projectiles::FireWandProjectile) + 5);
		break;
	case 11:
		stateData.savedPlayerData.setFireRateOfWeapon(Weapons::FireWand, stateData.savedPlayerData.getFireRateOfWeapons().at(Weapons::FireWand) - 0.1f);
		break;
	case 12:
		stateData.savedPlayerData.setManaCostOfShotOfFireWand(stateData.savedPlayerData.getManaCostOfShotOfFireWand() - 1);
		break;
	case 13:
		stateData.savedPlayerData.setDamageOfProjectile(Projectiles::IceWandProjectile, stateData.savedPlayerData.getDamageOfProjectiles().at(Projectiles::IceWandProjectile) + 5);
		break;
	case 14:
		stateData.savedPlayerData.setFreezOfIceWand(stateData.savedPlayerData.getFreezOfIceWand() + 0.5f);
		break;
	case 15:
		stateData.savedPlayerData.setManaCostOfShotOfIceWand(stateData.savedPlayerData.getManaCostOfShotOfIceWand() - 1);
		break;
	case 16:
		stateData.savedPlayerData.setDamageOfProjectile(Projectiles::PlaneBullet, stateData.savedPlayerData.getDamageOfProjectiles().at(Projectiles::PlaneBullet) + 5);
		break;
	case 17:
		stateData.savedPlayerData.setFireRateOfWeapon(Weapons::PlaneWeapon, stateData.savedPlayerData.getFireRateOfWeapons().at(Weapons::PlaneWeapon) - 0.1f);
		break;
	case 18:
		stateData.savedPlayerData.setDamageOfProjectile(Projectiles::ShadowWandProjectile, stateData.savedPlayerData.getDamageOfProjectiles().at(Projectiles::ShadowWandProjectile) + 5);
		break;
	case 19:
		stateData.savedPlayerData.setFireRateOfWeapon(Weapons::ShadowWand, stateData.savedPlayerData.getFireRateOfWeapons().at(Weapons::ShadowWand) - 0.1f);
		break;
	}*/
