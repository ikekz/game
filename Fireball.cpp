#include "Actor.h"
#include "Point.h"
#include <iostream>

using namespace std;

map<Point, char> Fireball::ways = {
	{ Point(-1, 0), '^' },
	{ Point(1, 0), 'v' },
	{ Point(0, -1), '<' },
	{ Point(0, 1), '>' }
};

Fireball::Fireball(Point& position, Point& way) : Actor(position), way(way) {};

char Fireball::Symbol()
{
	return ways.find(way)->second;
}

void Fireball::Action(Map& map)
{

}