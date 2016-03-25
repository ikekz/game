#include "Actor.h"
#include <set>
#include <iostream>
#include <iterator>

using namespace std;

Character::Character(Point& position, int health, int damage) : Actor(position), health(health), damage(damage)
{
	ways.insert(make_pair("w", Point(-1, 0)));
	ways.insert(make_pair("s", Point(1, 0)));
	ways.insert(make_pair("a", Point(0, -1)));
	ways.insert(make_pair("d", Point(0, 1)));
}

void Character::Action(std::vector<std::vector<Actor*>>& map)
{
	Move(map);
}

int Character::Health()
{
	return health;
}

void Character::SetPos(Point& pos)
{
	this->pos = pos;
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

char Hero::Symbol()
{
	return HERO;
}

void Hero::Move(vector<vector<Actor*>>& map)
{
	string s;
	cin >> s;

	if (ways.find(s) == ways.end())
	{
		cout << "Enter the correct action" << endl;
		Move(map);
		return;
	}

	Collide(*map[(pos + ways[s]).x][(pos + ways[s]).y], map);
}

void Princess::Collide(Monster& src, std::vector<std::vector<Actor*>>& map)
{
	src.Move(map);
}