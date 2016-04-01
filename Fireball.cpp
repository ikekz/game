#include "Fireball.h"
#include "Character.h"
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

int Fireball::Damage()
{
	return 200;
}

void Fireball::Action(Map& map)
{
	Collide(map[pos + way], map);
}

map<Point, char>& Fireball::GetWays()
{
	return ways;
}

void Fireball::Collide(Actor* src, Map& map)
{
	src->Collide(this, map);
}

void Fireball::Collide(Character* src, Map& map)
{
	src->TakeDamage(Damage());
	if (src->Health() <= 0)
		map.Clear(src->Pos());
	map.Clear(pos);
	map.Swap(map[src->Pos()], map[pos]);
	map.SetActed(src->Pos(), 1);
	delete this;
}

void Fireball::Collide(Fireball* src, Map& map)
{
	map.Clear(pos);
	map.Clear(src->Pos());
	delete src;
	delete this;
}