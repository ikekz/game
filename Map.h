#pragma once
#include <vector>
#include "Point.h"

#define WALL '#'
#define SPACE '.'

class Map
{
public:
	Map(int size);
	void GenMap();
	void RenderMap();
	int Size();
	void ChangeSymbol(Point& pos, char);
	char Symbol(Point& pos);
	bool CheckWay(int x, int y);
	void Clear(Point& pos);
private:
	int size;
	char** map;
};
