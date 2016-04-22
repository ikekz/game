#include "Cfg.h"

Cfg& Cfg::GetInstance()
{
	static Cfg cfg;
	return cfg;
}

Cfg::Cfg()
{
	SetImporter();
	SetVar();
}

void Cfg::SetImporter()
{
	importer = new Importer("config.txt");
}

void Cfg::SetVar()
{
	knightSymbol = importer->GetChar("knight", "symbol");
	princessSymbol = importer->GetChar("princess", "symbol");
	zombieSymbol = importer->GetChar("zombie", "symbol");
	dragonSymbol = importer->GetChar("dragon", "symbol");
	wizardSymbol = importer->GetChar("wizard", "symbol");
	nestSymbol = importer->GetChar("nest", "symbol");
	cemeterySymbol = importer->GetChar("cemetery", "symbol");
	wallSymbol = importer->GetChar("wall", "symbol");
	spaceSymbol = importer->GetChar("space", "symbol");
	medkitSymbol = importer->GetChar("medkit", "symbol");

	knightHealth = importer->GetInt("knight", "health");
	zombieHealth = importer->GetInt("zombie", "health");
	dragonHealth = importer->GetInt("dragon", "health");
	princessHealth = importer->GetInt("princess", "health");
	wizardHealth = importer->GetInt("wizard", "health");

	knightDamage = importer->GetInt("knight", "damage");
	zombieDamage = importer->GetInt("zombie", "damage");
	dragonDamage = importer->GetInt("dragon", "damage");
	wizardDamage = importer->GetInt("wizard", "damage");
	fireballDamage = importer->GetInt("fireball", "damage");
	princessDamage = importer->GetInt("princess", "damage");

	cemeteryCooldown = importer->GetInt("cemetery", "cooldown");
	nestCooldown = importer->GetInt("nest", "cooldown");
	medkitCooldown = importer->GetInt("medkit", "cooldown");

	medkitMaxCount = importer->GetInt("medkit", "maxCount");

	medkitPowerHeal = importer->GetInt("medkit", "powerHeal");
}
