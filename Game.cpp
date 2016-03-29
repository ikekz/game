#include "Game.h"
#include "Point.h"
#include <iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;

Game::Game(int sizeMap) : map(sizeMap) {};

void Game::CreateCharacter()
{
	CreateZombie(15);
	CreateDragon(9);
	CreateWizard(5);
}

void Game::CreateZombie(int count)
{
	for (int i = 0; i < count; i++)
	{
		Zombie* z = new Zombie(rand() % (map.Size() - 2) + 1, rand() % (map.Size() - 2) + 1);
		map.map[z->Pos().x][z->Pos().y] = z;
	}
}

void Game::CreateDragon(int count)
{
	for (int i = 0; i < count; i++)
	{
		Dragon* d = new Dragon(rand() % (map.Size() - 2) + 1, rand() % (map.Size() - 2) + 1);
		map.map[d->Pos().x][d->Pos().y] = d;
	}
}

void Game::CreateWizard(int count)
{
	for (int i = 0; i < count; i++)
	{
		Wizard* d = new Wizard(rand() % (map.Size() - 2) + 1, rand() % (map.Size() - 2) + 1);
		map.map[d->Pos().x][d->Pos().y] = d;
	}
}

bool Game::IsEnd()
{
	if (((Hero*)map.hero)->Health() <= 0 || map.hero->Pos() == map.princess->Pos())
		return 1;
	else
		return 0;
}

void Game::Start()
{
	srand(time(0));
	map.GenMap();
	CreateCharacter();
	map.PlaceHeroes();

	while (!IsEnd())
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

	if (((Hero*)map.hero)->Health() > 0)
		cout << "YOU WON!\n" << endl;
	else
		cout << "GAME OVER\n" << endl;
}

void Game::Move()
{
	cout << "Hero health: " << ((Hero*)map.hero)->Health() << endl;

	vector<vector<Actor*>> buf = map.map;
	Point tmp = map.hero->Pos();
	buf[tmp.x][tmp.y] = buf[0][0];
	buf[0][0] = map.hero;

	for (int i = 0; i < map.Size(); i++)
		for (int j = 0; j < map.Size(); j++)
			if (((Character*)buf[i][j])->Health() > 0)
				buf[i][j]->Action(map);
}