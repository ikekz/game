#include "Game.h"
#include "Point.h"
#include <iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;

Game::Game(int sizeMap) : end(0), map(sizeMap), hero(new Hero(sizeMap - 1, 0)), princess(new Princess(0, sizeMap - 1)) {};

void Game::CreateCharacter()
{
	CreateZombie(15);
	CreateDragon(9);
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

		if (chs[i]->Pos() == hero->Pos() || chs[i]->Pos() == princess->Pos())
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
		system("cls");
		map.RenderMap();
		Move();	
	}

	PrintStatus();
}

void Game::PrintStatus()
{
	system("cls");

	if (hero->Health() > 0)
		cout << "YOU WON!\n" << endl;
	else
		cout << "GAME OVER\n" << endl;
}

void Game::Move()
{
	cout << "Hero health: " << hero->Health() << endl;

	Point pos = hero->Move(map);
	if (pos == princess->Pos())
	{
		end = 1;
		return;
	}

	for (int i = 0; i < chs.size(); i++)
		if (pos == chs[i]->Pos())
		{
			map.Clear(hero->Pos());
			hero->Interaction(*chs[i]);
			if (chs[i]->Health() <= 0)
			{
				hero->SetPos(pos);
				chs.erase(chs.begin() + i);
			}
			map.ChangeSymbol(hero->Pos(), hero->Symbol());
		}

	for (int i = 0; i < chs.size(); i++)
	{
		Point pos = chs[i]->Move(map);
		if (pos == hero->Pos())
		{
			chs[i]->Interaction(*hero);
			if (hero->Health() <= 0)
				end = 1;
		}
	}
	
	FeelMap();
}