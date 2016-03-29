#pragma once
#include <vector>
#include "Point.h"

#define WALL '#'
#define SPACE '.'

class Actor;

class Map
{
public:
	Map(int size);
	void GenMap();
	void RenderMap();
	int Size();
	Actor* operator[](const Point&);
	bool CheckWay(char** buf, int x, int y);
	void Swap(Actor*, Actor*);
	void PlaceHeroes();
	Point CalcWay(Point&, Point&);
	std::vector<std::vector<Actor*>> map;
	Actor* hero;
	Actor* princess;
};
