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

Princess::Princess(int x, int y) : Character(0, 0, Point(x, y)) {}

Point Princess::Move(Map& map)
{
	return Point(-1, -1);
}

char Princess::Symbol()
{
	return PRINCESS;
}

Hero::Hero(int x, int y) : Character(500, 50, Point(x, y)) {}

void Hero::Interaction(Character& ch)
{
	ch.Interaction(*this);
}

void Hero::Interaction(Monster& monster)
{
	TakeDamage(monster);
}

Point Hero::Move(Map& map)
{
	string s;
	cin >> s;

	if (ways.find(s) == ways.end())
	{
		cout << "Enter the correct action" << endl;
		Move(map);
		return Point(-1, -1);
	}

	Point step = ways[s];
	if (pos + step > Point(-1, -1) && pos + step < Point(map.Size(), map.Size()) &&
		map.Symbol(pos + step) != WALL)
	{
		if (map.Symbol(pos + step) == SPACE)
		{
			map.Clear(pos);
			pos = pos + step;
			map.ChangeSymbol(pos, Symbol());
		}
		else
			return pos + step;
	}
	else
	{
		cout << "Enter the correct action" << endl;
		Move(map);
	}

	return Point(-1, -1);
}

char Hero::Symbol()
{
	return HERO;
}

Monster::Monster(int health, int damage, Point& position) : Character(health, damage, position) {}

void Monster::Interaction(Character& ch)
{
	ch.Interaction(*this);
}

void Monster::Interaction(Hero& hero)
{
	TakeDamage(hero);
}

Point Monster::Move(Map& map)
{
	std::map<string, Point>::iterator it = ways.begin();
	advance(it, rand() % ways.size());
	for (int i = 0; i < ways.size(); it++, it = it == ways.end() ? ways.begin() : it, i++)
		if (pos + it->second > Point(-1, -1) && pos + it->second < Point(map.Size(), map.Size()) &&
			map.Symbol(pos + it->second) != WALL)
			if (map.Symbol(pos + it->second) == SPACE)
			{
				map.Clear(pos);
				pos = pos + it->second;
				map.ChangeSymbol(pos, Symbol());
				break;
			}
			else
				return pos + it->second;

	return Point(-1, -1);
}

Zombie::Zombie(int x, int y) : Monster(50, 50, Point(x, y)) {};

char Zombie::Symbol()
{
	return ZOMBIE;
}

Dragon::Dragon(int x, int y) : Monster(100, 150, Point(x, y)) {};

char Dragon::Symbol()
{
	return DRAGON;
}
