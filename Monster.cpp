#include "Actor.h"
#include <set>
#include <iostream>
#include <iterator>

using namespace std;

Monster::Monster(Point& position, int health, int damage) : Character(position, health, damage) {}

Point Monster::SelectWay()
{
	if (step.y > 4)
		return Point(0, 0);

	std::map<string, Point>::iterator it = ways.begin();
	step.x = (step.x + 1) % ways.size();

	if (step.y == 0)
	{
		step.x = rand() % ways.size();
		step.y++;
	}

	advance(it, step.x);
	return it->second;
}

void Monster::Move(vector<vector<Actor*>>& map)
{
	Point way = SelectWay();

	Collide(*map[(pos + way).x][(pos + way).y], map);

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

void Hero::Collide(Actor& src, std::vector<std::vector<Actor*>>& map)
{
	src.Collide(*this, map);
}

void Hero::Collide(Monster& src, std::vector<std::vector<Actor*>>& map)
{
	TakeDamage(src);
}

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

void Princess::Collide(Hero& src, std::vector<std::vector<Actor*>>& map)
{
	src.SetPos(pos);
}

Wizard::Wizard(int x, int y) : Monster(Point(x, y), 50, 10) {}

char Wizard::Symbol()
{
	return WIZARD;
}

void Wizard::Move(std::vector<std::vector<Actor*>>& map)
{
	Point way = SelectWay();

	Collide(*map[(pos + way).x][(pos + way).y], map);
}