#include "Map.h"
#include <iostream>
#include "DFS.h"
#include "Character.h"
#include "Block.h"

using namespace std;

Map::Map(int size) : hero(new Hero(size - 2, 1)), princess(new Princess(1, size - 2))
{
	map.resize(size);
	acted.resize(size);
	for (int i = 0; i < size; i++)
	{
		map[i].resize(size);
		acted[i].resize(size);
	}
};

int Map::Size()
{
	return map.size();
}

void Map::RefreshActed()
{
	for (int i = 0; i < Size(); i++)
		for (int j = 0; j < Size(); j++)
			acted[i][j] = 0;
}

Actor* Map::operator[](const Point& src)
{
	return map[src.x][src.y];
}

Point Map::CalcWay(Point& from, Point& to)
{
	if (from.x == to.x)
		return Point(0, from.y > to.y ? -1 : 1);
	else if (from.y == to.y)
		return Point(from.x > to.x ? -1 : 1, 0);
	else
		return Point(-1, -1);
}

void Map::PlaceHeroes()
{
	map[hero->Pos().x][hero->Pos().y] = hero;
	map[princess->Pos().x][princess->Pos().y] = princess;
}

void Map::Swap(Actor* src1, Actor* src2)
{
	Point tmp = src1->Pos();

	src1->SetPos(src2->Pos());
	map[src2->Pos().x][src2->Pos().y] = src1;

	src2->SetPos(tmp);
	map[src2->Pos().x][src2->Pos().y] = src2;
}

void Map::Clear(Point& src)
{
	map[src.x][src.y] = new Space(Point(src.x, src.y));
}

Actor* Map::GetHero()
{
	return hero;
}

Actor* Map::GetPrincess()
{
	return princess;
}

void Map::SetActed(Point& pos, bool src)
{
	acted[pos.x][pos.y] = src;
}

void Map::Insert(Point& pos, Actor* src)
{
	map[pos.x][pos.y] = src;
}

bool Map::IsActed(Point& pos)
{
	return acted[pos.x][pos.y];
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
			buf[i][j] = Cfg::GetInstance().SpaceSymbol();
	}

	for (int i = 0; i < map.size(); i++)
		buf[i][0] = buf[i][map.size() - 1] = buf[0][i] = buf[map.size() - 1][i] = Cfg::GetInstance().WallSymbol();

	for (int i = 0; i < 40; i++)
		buf[rand() % (map.size() - 1) + 1][rand() % (map.size() - 1) + 1] = Cfg::GetInstance().WallSymbol();

	if (!CheckWay(buf, map.size() - 2, 1))
		GenMap();
	else
	{
		for (int i = 0; i < map.size(); i++)
			for (int j = 0; j < map.size(); j++)
				if (buf[i][j] == Cfg::GetInstance().WallSymbol())
					map[i][j] = new Wall(Point(i, j));
				else
					map[i][j] = new Space(Point(i, j));
		RefreshActed();
	}
}