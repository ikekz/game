#pragma once
#include "Character.h"
#include "Map.h"

class Game
{
public:
	void Start();
	void CreateCharacter();
	//void CreateHero();
	void CreateZombie(int count);
	void CreateDragon(int count);
	//void CreatePricess();
	void CheckConflict();
	void Move();
	Game(int sizeMap = 10);
	void FeelMap();
private:
	Map map;
	std::vector<Character*> chs;
	Hero* hero;
	Princess* princess;
	bool end;
};