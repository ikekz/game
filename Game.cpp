#include "Game.h"
#include "Point.h"
#include <iostream>
#include <ctime>

using namespace std;

Game::Game(int sizeMap) : end(0), map(sizeMap), hero(new Hero(sizeMap - 1, 0)), princess(new Princess(0, sizeMap - 1)) {};

void Game::CreateCharacter()
{
	CreateZombie(10);
	CreateDragon(5);
	CheckConflict();
	FeelMap();
}

void Game::CreateZombie(int count)
{
	for (int i = 0; i < count; i++)
		chs.push_back(new Zombie(rand() % map.Size(), rand() % map.Size()));
}

void Game::CreateDragon(int count)
{
	for (int i = 0; i < count; i++)
		chs.push_back(new Dragon(rand() % map.Size(), rand() % map.Size()));
}

void Game::CheckConflict()
{
	for (int i = 0; i < chs.size(); i++)
	{
		for (int j = i + 1; j < chs.size(); j++)
			if (chs[i]->Pos() == chs[j]->Pos())
				chs.erase(chs.begin() + j);

		if (chs[i]->Pos() == hero->Pos())
			chs.erase(chs.begin() + i);

		if (chs[i]->Pos() == princess->Pos())
			chs.erase(chs.begin() + i);
	}
}

void Game::FeelMap()
{
	map.ChangeSymbol(hero->Pos(), hero->Symbol());

	map.ChangeSymbol(princess->Pos(), princess->Symbol());

	for (int i = 0; i < chs.size(); i++)
		map.ChangeSymbol(chs[i]->Pos(), chs[i]->Symbol());
}

void Game::Start()
{
	srand(time(0));
	map.GenMap();
	CreateCharacter();
	while (!end)
	{
		map.RenderMap();
		Move();
	}
	if (hero->Health() > 0)
		cout << "YOU WON!\n" << endl;
	else
		cout << "GAME OVER\n" << endl;
}

void Game::Move()
{
	cout << "Hero health: " << hero->Health() << endl;

	hero->Move(map);
	for (int i = 0; i < chs.size(); i++)
		chs[i]->Move(map);

	for (int j = 0; j < chs.size(); j++)
		if (hero->Pos() == chs[j]->Pos())
			if (hero->Fight(*chs[j]))
				chs.erase(chs.begin() + j);
			else
				end = 1;
	
	if (hero->Pos() == princess->Pos())
		end = 1;

	FeelMap();
}