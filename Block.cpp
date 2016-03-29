#include "Actor.h"
#include <iostream>

using namespace std;

Wall::Wall(Point& position) : Actor(position) {}

Space::Space(Point& position) : Actor(position) {}

char Wall::Symbol()
{
	return WALL;
}

char Space::Symbol()
{
	return SPACE;
}

void Space::Collide(Character* src, Map& map)
{
	map.Swap(src, this);
}

void Wall::Collide(Character* src, Map& map)
{
	src->Move(map);
}