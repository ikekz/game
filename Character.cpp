#include "Actor.h"
#include <set>
#include <iostream>
#include <iterator>

using namespace std;

map<string, Point> Character::ways = {
	{ "w", Point(-1, 0)},
	{ "s", Point(1, 0)},
	{ "a", Point(0, -1)},
	{ "d", Point(0, 1)}
};

Character::Character(Point& position, int health, int damage) : Actor(position), health(health), damage(damage) {}

void Character::Action(Map& map)
{
	Move(map);
}

void Hero::Collide(Actor& src, Map& map)
{
	src.Collide(*this, map);
}

int Character::Health()
{
	return health;
}

void Character::TakeDamage(Character& enemy)
{
	health -= enemy.damage;
}

Princess::Princess(int x, int y) : Character(Point(x, y), 0, 0) {}

char Princess::Symbol()
{
	return PRINCESS;
}

Hero::Hero(int x, int y) : Character(Point(x, y), 500, 50) {}

void Hero::Collide(Monster& src, Map& map)
{
	TakeDamage(src);
}

char Hero::Symbol()
{
	return HERO;
}

void Hero::Move(Map& map)
{
	string s;
	cin >> s;

	if (ways.find(s) == ways.end())
	{
		cout << "Enter the correct action" << endl;
		Move(map);
		return;
	}

	Collide(*map.map[(pos + ways[s]).x][(pos + ways[s]).y], map); //
}