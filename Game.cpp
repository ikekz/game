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
		map.Insert(z->Pos(), z);
	}
}

void Game::CreateDragon(int count)
{
	for (int i = 0; i < count; i++)
	{
		Dragon* d = new Dragon(rand() % (map.Size() - 2) + 1, rand() % (map.Size() - 2) + 1);
		map.Insert(d->Pos(), d);
	}
}

void Game::CreateWizard(int count)
{
	for (int i = 0; i < count; i++)
	{
		Wizard* w = new Wizard(rand() % (map.Size() - 2) + 1, rand() % (map.Size() - 2) + 1);
		map.Insert(w->Pos(), w);
	}
}

void Game::CreateSpawner()
{
	Cemetry* c = new Cemetry(Point(rand() % (map.Size() - 2) + 1, rand() % (map.Size() - 2) + 1));
	map.Insert(c->Pos(), c);

	Nest* n = new Nest(Point(rand() % (map.Size() - 2) + 1, rand() % (map.Size() - 2) + 1));
	map.Insert(n->Pos(), n);
}

bool Game::IsEnd()
{
	if (((Hero*)map.GetHero())->Health() <= 0 || map.GetHero()->Pos() == map.GetPrincess()->Pos())
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
			if (map[Point(p, k)]->Symbol() == SPACE)
			{
				map.Insert(Point(p, k), new Medkit(Point(p, k)));
				i = j = map.Size();
			}
}

void Game::PrintStatus()
{
	system("cls");

	if (((Hero*)map.GetHero())->Health() > 0)
		cout << "YOU WON!\n" << endl;
	else
		cout << "GAME OVER\n" << endl;
}

void Game::Act()
{
	cout << "Hero health: " << ((Hero*)map.GetHero())->Health() << endl;
	//сделать мап указателем
	
	map.GetHero()->Action(map);
	for (int i = 0; i < map.Size(); i++)
		for (int j = 0; j < map.Size(); j++)
			if (!map.IsActed(Point(i, j)))
				map[Point(i, j)]->Action(map);
	map.RefreshActed();

	actNumber++;
	if (actNumber % 3 == 0 && Medkit::Count() < 5)
		CreateMedkit();
}