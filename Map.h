#pragma once
#include <vector>
#include "Point.h"
#include "Character.h"

#define WALL '#'
#define SPACE '.'

class Map
{
public:
	Map(int size);
	void GenMap();
	void RenderMap();
	int Size();
	Actor* operator[](const Point&);
	bool CheckWay(char** buf, int x, int y);
	std::vector<std::vector<Actor*>> map;
private:
	int size;
};
