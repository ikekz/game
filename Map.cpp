#include "Map.h"
#include <iostream>
#include "DFS.h"

using namespace std;

Map::Map(int size) : size(size) {};

int Map::Size()
{
	return size;
}

void Map::ChangeSymbol(Point& pos, char c)
{
	map[pos.x][pos.y] = c;
}

char Map::Symbol(Point& pos)
{
	return map[pos.x][pos.y];
}

void Map::RenderMap()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			cout << map[i][j];
		cout << endl;
	}
}

void Map::Clear(Point& pos)
{
	map[pos.x][pos.y] = SPACE;
}

bool Map::CheckWay(int x, int y)
{
	char** buf = new char*[size];
	for (int i = 0; i < size; i++)
	{
		buf[i] = new char[size];
		for (int j = 0; j < size; j++)
			buf[i][j] = map[i][j];
	}
	return DFS(buf, size, x, y);
}

void Map::GenMap()
{
	map = new char*[size];
	for (int i = 0; i < size; i++)
	{
		map[i] = new char[size];
		for (int j = 0; j < size; j++)
			map[i][j] = SPACE;	
	}

	for (int i = 0; i < 40; i++)
		map[rand() % size][rand() % size] = WALL;

	if (!CheckWay(size - 1, 0))
		GenMap();
}