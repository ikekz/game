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
	map.acted[pos.x][pos.y] = 1;
}

int Character::Health()
{
	return health;
}

void Character::Collide(Actor* src, Map& map)
{
	src->Collide(this, map);
}

void Character::DealDamage(Character* enemy)
{
	enemy->health -= damage;
}

void Character::TakeDamage(int damage)
{
	health -= damage;
}

void Character::Collide(Fireball* src, Map& map)
{
	TakeDamage(src->Damage()); // сделать везде где можно обьеденить монстров в карактер
	if (Health() <= 0)
		map.Clear(pos);
	map.Clear(src->Pos());
	//map.Swap(map[src->Pos()], map[pos]);
}

Princess::Princess(int x, int y) : Character(Point(x, y), 0, 0) {}

char Princess::Symbol()
{
	return PRINCESS;
}

void Princess::Collide(Character* src, Map& map)
{
	src->Collide(this, map);
}

void Princess::Collide(Actor* src, Map& map)
{
	src->Collide(this, map);
}

Hero::Hero(int x, int y) : Character(Point(x, y), 5000, 50) {}

void Hero::Collide(Character* src, Map& map)
{
	src->Collide(this, map);
}

void Hero::Collide(Actor* src, Map& map)
{
	src->Collide(this, map);
}

void Hero::Collide(Monster* src, Map& map)
{
	DealDamage(src);
	if (src->Health() <= 0)
	{
		map.Clear(src->Pos());
		map.Swap(map[src->Pos()], map[pos]);
	}
}

void Hero::Collide(Princess* src, Map& map)
{
	SetPos(src->Pos());
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

	Collide(map.map[(pos + ways[s]).x][(pos + ways[s]).y], map); //
}