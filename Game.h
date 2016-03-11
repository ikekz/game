#pragma once
#include "Character.h"
#include "Map.h"

class Game
{
public:
	void Start();
	void CreateCharacter();
	void CreateZombie(int count);
	void CreateDragon(int count);
	void PrintStatus();
	void CheckConflict();
	void Move();
	Game(int sizeMap = 10);
	void FeelMap();
private:
	Map map;
	std::vector<Character*> chs;
	Character* hero;
	Character* princess;
	bool end;
};