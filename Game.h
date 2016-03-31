#pragma once
#include "Actor.h"
#include "Map.h"

class Game
{
public:
	void Start();
	void CreateCharacter();
	void CreateZombie(int count);
	void CreateDragon(int count);
	void CreateWizard(int count);
	void PrintStatus();
	void CreateMedkit();
	void Act();
	Game(int sizeMap = 10);
	bool IsEnd();
	int ActNumber();
private:
	int actNumber = 0;
	Map map;
};