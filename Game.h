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
	void Move();
	Game(int sizeMap = 10);
	bool IsEnd();
private:
	Map map;
	Actor* hero;
	Actor* princess;
};