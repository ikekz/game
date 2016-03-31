#include "Game.h"
#include "Character.h"
#include "Point.h"
#include "Spawner.h"
#include "Medkit.h"
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

void Game::CreateSpawner()
{
	Cemetry* c = new Cemetry(Point(rand() % (map.Size() - 2) + 1, rand() % (map.Size() - 2) + 1));
	map.map[c->Pos().x][c->Pos().y] = c;

	Nest* n = new Nest(Point(rand() % (map.Size() - 2) + 1, rand() % (map.Size() - 2) + 1));
	map.map[n->Pos().x][n->Pos().y] = n;
}

bool Game::IsEnd()
{
	if (((Hero*)map.hero)->Health() <= 0 || map.hero->Pos() == map.princess->Pos())
		return 1;
	else
		return 0;
}

int Game::ActNumber()
{
	return actNumber;
}

void Game::Start()
{
	srand(time(0));
	map.GenMap();
	CreateCharacter();
	CreateSpawner();
	map.PlaceHeroes();

	while (!IsEnd())
	{
		system("cls");
		map.RenderMap();
		Act();	
	}
	
	PrintStatus();
}

void Game::CreateMedkit()
{
	for (int i = 1, p = rand() % (map.Size() - 2) + 1; i < map.Size(); i++, p++, p >= map.Size() ? p = 1 : p = p)
		for (int j = 1, k = rand() % (map.Size() - 2) + 1; j < map.Size(); j++, k++, k >= map.Size() ? k = 1 : k = k)
			if (map.map[p][k]->Symbol() == SPACE)
			{
				map.map[p][k] = new Medkit(Point(p, k));
				i = j = map.Size();
			}
}

void Game::PrintStatus()
{
	system("cls");

	if (((Hero*)map.hero)->Health() > 0)
		cout << "YOU WON!\n" << endl;
	else
		cout << "GAME OVER\n" << endl;
}

void Game::Act()
{
	cout << "Hero health: " << ((Hero*)map.hero)->Health() << endl;
	//сделать мап указателем
	
	map.hero->Action(map);
	for (int i = 0; i < map.Size(); i++)
		for (int j = 0; j < map.Size(); j++)
			if (!map.acted[i][j])
				map.map[i][j]->Action(map);
	map.RefreshActed();

	actNumber++;
	if (actNumber % 3 == 0 && Medkit::Count() < 5)
		CreateMedkit();
}