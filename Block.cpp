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

void Space::Collide(Actor& src, Map& map)
{
	map.Swap(src, *this);
}

void Space::Collide(Hero& src, Map& map)
{
	Collide(*(Actor*)(&src), map);
}

void Space::Collide(Monster& src, Map& map)
{
	Collide(*(Actor*)(&src), map);
}

void Wall::Collide(Hero& src, Map& map)
{
	cout << "Enter the correct action" << endl;
	src.Move(map);
}

void Wall::Collide(Monster& src, Map& map)
{
	src.Move(map);
}