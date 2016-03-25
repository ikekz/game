#include "Character.h"
#include <set>
#include <iostream>
#include <iterator>

using namespace std;

Actor::Actor(Point& position) : pos(position) {};

Point Actor::Pos()
{
	return pos;
}

char Wall::Symbol()
{
	return '#';
}

char Space::Symbol()
{
	return '.';
}

Character::Character(Point& position, int health, int damage) : Actor(position), health(health), damage(damage)
{
	ways.insert(make_pair("w", Point(-1, 0)));
	ways.insert(make_pair("s", Point(1, 0)));
	ways.insert(make_pair("a", Point(0, -1)));
	ways.insert(make_pair("d", Point(0, 1)));
}

void Character::Collide(Character& src, std::vector<std::vector<Actor*>>& map)
{
	//Collide()
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

void Hero::Collide(Actor& src, std::vector<std::vector<Actor*>>& map)
{
	src.Collide(*this, map);
}

void Hero::Collide(Monster& src, std::vector<std::vector<Actor*>>& map)
{
	TakeDamage(src);
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

	Point step = ways[s];
	if (pos + step > Point(-1, -1) && pos + step < Point(map.size(), map.size()))
	{
		Collide(*map[(pos + step).x][(pos + step).y], map);
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

Monster::Monster(Point& position, int health, int damage) : Character(position, health, damage) {}

void Monster::Collide(Actor& src, std::vector<std::vector<Actor*>>& map)
{
	src.Collide(*this, map);
}

void Monster::Collide(Hero& src, std::vector<std::vector<Actor*>>& map)
{
	TakeDamage(src);
	if (health <= 0)
	{
		Point tmp = src.Pos();

		src.SetPos(pos);
		map[pos.x][pos.y] = &src;

		map[tmp.x][tmp.y] = new Space(Point(tmp.x, tmp.y));
	}
}

void Monster::Move(vector<vector<Actor*>>& map)
{
	std::map<string, Point>::iterator it = ways.begin();
	advance(it, rand() % ways.size());
}

Zombie::Zombie(int x, int y) : Monster(Point(x, y), 50, 50) {};

char Zombie::Symbol()
{
	return ZOMBIE;
}

Dragon::Dragon(int x, int y) : Monster(Point(x, y), 100, 150) {};

char Dragon::Symbol()
{
	return DRAGON;
}

void Space::Collide(Hero& src, std::vector<std::vector<Actor*>>& map)
{
	Point tmp = src.Pos();

	src.SetPos(pos);
	map[pos.x][pos.y] = &src;

	pos = tmp;
	map[pos.x][pos.y] = this;
};

void Wall::Collide(Hero& src, std::vector<std::vector<Actor*>>& map)
{
	cout << "Enter the correct action" << endl;
	src.Move(map);
}
