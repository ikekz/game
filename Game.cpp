#include "Game.h"
#include "Point.h"
#include <iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;

Game::Game(int sizeMap) : map(sizeMap), hero(new Hero(sizeMap - 1, 0)), princess(new Princess(0, sizeMap - 1)) {};

void Game::CreateCharacter()
{
	CreateZombie(15);
	CreateDragon(9);
}

void Game::CreateZombie(int count)
{
	for (int i = 0; i < count; i++)
	{
		Zombie* z = new Zombie(rand() % map.Size(), rand() % map.Size());
		map.map[z->Pos().x][z->Pos().y] = z;
	}
}

void Game::CreateDragon(int count)
{
	for (int i = 0; i < count; i++)
	{
		Dragon* d = new Dragon(rand() % map.Size(), rand() % map.Size());
		map.map[d->Pos().x][d->Pos().y] = d;
	}
}

bool Game::IsEnd()
{
	if (((Hero*)hero)->Health() <= 0 || hero->Pos() == princess->Pos())
		return 1;
	else
		return 0;
}

void Game::Start()
{
	srand(time(0));
	map.GenMap();
	CreateCharacter();
	map.map[hero->Pos().x][hero->Pos().y] = hero;
	map.map[princess->Pos().x][princess->Pos().y] = princess;
	
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

	if (((Hero*)hero)->Health() > 0)
		cout << "YOU WON!\n" << endl;
	else
		cout << "GAME OVER\n" << endl;
}

void Game::Move()
{
	cout << "Hero health: " << ((Hero*)hero)->Health() << endl;

	vector<vector<Actor*>> buf = map.map;

	for (int i = 0; i < map.Size(); i++)
		for (int j = 0; j < map.Size(); j++)
			buf[i][j]->Action(map.map);
}