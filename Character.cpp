#include "Character.h"
#include <set>
#include <iostream>
#include <iterator>

using namespace std;

Character::Character(int health, int damage, Point& position) : health(health), damage(damage), pos(position)
{
	ways.insert(make_pair("w", Point(-1, 0)));
	ways.insert(make_pair("s", Point(1, 0)));
	ways.insert(make_pair("a", Point(0, -1)));
	ways.insert(make_pair("d", Point(0, 1)));
}

Point Character::Pos()
{
	return pos;
}

bool Character::Fight(Character& enemy)
{
	while (health > 0 && enemy.health > 0)
	{
		TakeDamage(enemy);
		DealDamage(enemy);
	}

	if (health > 0)
		return 1;
	else
		return 0;
}

int Character::Health()
{
	return health;
}

void Character::TakeDamage(Character& enemy)
{
	health -= enemy.damage;
}

void Character::DealDamage(Character& enemy)
{
	enemy.health -= damage;
}

Princess::Princess(int x, int y) : Character(0, 0, Point(x, y)) {}

void Princess::Move(Map& map) {}

char Princess::Symbol()
{
	return PRINCESS;
}

Hero::Hero(int x, int y) : Character(500, 50, Point(x, y)) {}

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
	Point step = ways[s];
	if (pos + step > Point(-1, -1) && pos + step < Point(map.Size(), map.Size()) &&
		map.Symbol(pos + step) != WALL)
	{
		map.Clear(pos);
		pos = pos + step;
	}
	else
	{
		cout << "Enter the correct action" << endl;
		Move(map);
	}
}

char Hero::Symbol()
{
	return HERO;
}

Monster::Monster(int health, int damage, Point& position) : Character(health, damage, position) {}

void Monster::Move(Map& map)
{
	std::set<char> let = { WALL, ZOMBIE, DRAGON, PRINCESS };

	std::map<string, Point>::iterator it = ways.begin();
	advance(it, rand() % ways.size());
	for (int i = 0; i < ways.size(); it++, it = it == ways.end() ? ways.begin() : it, i++)
		if (pos + it->second > Point(-1, -1) && pos + it->second < Point(map.Size(), map.Size()) &&
			let.find(map.Symbol(pos + it->second)) == let.end())
		{
			map.Clear(pos);
			pos = pos + it->second;
			map.ChangeSymbol(pos, Symbol());
			break;
		}
}

Zombie::Zombie(int x, int y) : Monster(100, 50, Point(x, y)) {};

char Zombie::Symbol()
{
	return ZOMBIE;
}

Dragon::Dragon(int x, int y) : Monster(200, 75, Point(x, y)) {};

char Dragon::Symbol()
{
	return DRAGON;
}
