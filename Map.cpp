#include "Map.h"
#include <iostream>
#include "DFS.h"

using namespace std;

Map::Map(int size) 
{
	map.resize(size);
	for (int i = 0; i < size; i++)
		map[i].resize(size);
};

int Map::Size()
{
	return map.size();
}

Actor* Map::operator[](const Point& src)
{
	return map[src.x][src.y];
}

void Map::RenderMap()
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map.size(); j++)
			cout << map[i][j]->Symbol();
		cout << endl;
	}
}

bool Map::CheckWay(char** buf, int x, int y)
{
	char** tmp = new char*[map.size()];
	for (int i = 0; i < map.size(); i++)
	{
		tmp[i] = new char[map.size()];
		for (int j = 0; j < map.size(); j++)
			tmp[i][j] = buf[i][j];
	}
	return DFS(tmp, map.size(), x, y);
}

void Map::GenMap()
{
	char** buf = new char*[map.size()];
	for (int i = 0; i < map.size(); i++)
	{
		buf[i] = new char[map.size()];
		for (int j = 0; j < map.size(); j++)
			buf[i][j] = SPACE;
	}

	for (int i = 0; i < map.size(); i++)
		buf[i][0] = buf[i][map.size() - 1] = buf[0][i] = buf[map.size() - 1][i] = WALL;

	for (int i = 0; i < 40; i++)
		buf[rand() % (map.size() - 1) + 1][rand() % (map.size() - 1) + 1] = WALL;

	if (!CheckWay(buf, map.size() - 2, 1))
		GenMap();
	else
		for (int i = 0; i < map.size(); i++)
			for (int j = 0; j < map.size(); j++)
				if (buf[i][j] == WALL)
					map[i][j] = new Wall(Point(i, j));
				else
					map[i][j] = new Space(Point(i, j));

}