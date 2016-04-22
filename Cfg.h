#pragma once
#include "Importer.h"

class Cfg
{
public:
	static Cfg& GetInstance();
	char KnightSymbol() { return knightSymbol; }
	char PrincessSymbol() { return princessSymbol; }
	char ZombieSymbol() { return zombieSymbol; }
	char DragonSymbol() { return dragonSymbol; }
	char CemeterySymbol() { return cemeterySymbol; }
	char NestSymbol() { return nestSymbol; }
	char WizardSymbol() { return wizardSymbol; }
	char WallSymbol() { return wallSymbol; }
	char SpaceSymbol() { return spaceSymbol; }
	char MedkitSymbol() { return medkitSymbol; }

	int KnightHealth() { return knightHealth; }
	int ZombieHealth() { return zombieHealth; }
	int DragonHealth() { return dragonHealth; }
	int WizardHealth() { return wizardHealth; }
	int PrincessHealth() { return princessHealth; }

	int KnightDamage() { return knightDamage; }
	int ZombieDamage() { return zombieDamage; }
	int DragonDamage() { return dragonDamage; }
	int FireballDamage() { return fireballDamage; }
	int WizardDamage() { return wizardDamage; }
	int PrincessDamage() { return princessDamage; }

	int CemeteryCooldown() { return cemeteryCooldown; }
	int NestCooldown() { return nestCooldown; }
	int MedkitCooldown() { return medkitCooldown; }

	int MedkitMaxCount() { return medkitMaxCount; }

	int MedkitPowerHeal() { return medkitPowerHeal; }
private:
	void SetImporter();
	void SetVar();
	Importer* importer;
	Cfg();

	char knightSymbol;
	char princessSymbol;
	char zombieSymbol;
	char dragonSymbol;
	char cemeterySymbol;
	char nestSymbol;
	char wizardSymbol;
	char wallSymbol;
	char spaceSymbol;
	char medkitSymbol;

	int knightHealth;
	int zombieHealth;
	int dragonHealth;
	int wizardHealth;
	int princessHealth;

	int knightDamage;
	int zombieDamage;
	int dragonDamage;
	int fireballDamage;
	int wizardDamage;
	int princessDamage;

	int cemeteryCooldown;
	int nestCooldown;
	int medkitCooldown;
	
	int medkitMaxCount;
	
	int medkitPowerHeal;
};