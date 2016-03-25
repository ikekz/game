#include "Map.h"
#include <iostream>
#include "DFS.h"

using namespace std;

Map::Map(int size) : size(size) 
{
	map.resize(size);
	for (int i = 0; i < size; i++)
		map[i].resize(size);
};

int Map::Size()
{
	return size;
}

Actor* Map::operator[](const Point& src)
{
	return map[src.x][src.y];
}

void Map::RenderMap()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			cout << map[i][j]->Symbol();
		cout << endl;
	}
}

bool Map::CheckWay(char** buf, int x, int y)
{
	char** tmp = new char*[size];
	for (int i = 0; i < size; i++)
	{
		tmp[i] = new char[size];
		for (int j = 0; j < size; j++)
			tmp[i][j] = buf[i][j];
	}
	return DFS(tmp, size, x, y);
}

void Map::GenMap()
{
	char** buf = new char*[size];
	for (int i = 0; i < size; i++)
	{
		buf[i] = new char[size];
		for (int j = 0; j < size; j++)
			buf[i][j] = SPACE;
	}

	for (int i = 0; i < 40; i++)
		buf[rand() % size][rand() % size] = WALL;

	if (!CheckWay(buf, size - 1, 0))
		GenMap();
	else
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				if (buf[i][j] == WALL)
					map[i][j] = new Wall(Point(i, j));
				else
					map[i][j] = new Space(Point(i, j));
			

}