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

void Monster::Move(Map& map)
{
	Point way = SelectWay();

	Collide(map.map[(pos + way).x][(pos + way).y], map);

	step.y = 0;
}

Zombie::Zombie(int x, int y) : Monster(Point(x, y), 50, 50) {}

char Zombie::Symbol()
{
	return ZOMBIE;
}

Dragon::Dragon(int x, int y) : Monster(Point(x, y), 100, 150) {}

char Dragon::Symbol()
{
	return DRAGON;
}

void Monster::Collide(Actor* src, Map& map)
{
	src->Collide(this, map);
}

void Monster::Collide(Character* src, Map& map)
{
	src->Collide(this, map);
}

void Monster::Collide(Hero* src, Map& map)
{
	DealDamage(src);
}

void Monster::Collide(Monster* src, Map& map)
{
	Move(map);
}

Wizard::Wizard(int x, int y) : Monster(Point(x, y), 50, 10) {}

char Wizard::Symbol()
{
	return WIZARD;
}

Fireball* Wizard::CreateFireball(Point& way, Map& map)
{
	map.acted[(pos + way).x][(pos + way).y] = 1;
	return new Fireball(pos + way, way);
}

void Wizard::Action(Map& map)
{
	Point way = map.CalcWay(pos, map.hero->Pos());
	if ((pos.x == map.hero->Pos().x || pos.y == map.hero->Pos().y) && map.map[(pos + way).x][(pos + way).y]->Symbol() == SPACE)
		map.map[(pos + way).x][(pos + way).y] = CreateFireball(way, map);
	else 
		Move(map);
	map.acted[pos.x][pos.y] = 1;
}