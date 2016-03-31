#include "Fireball.h"
#include "Character.h"
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

void Princess::Collide(Fireball* src, Map& map)
{
	map.Clear(src->Pos());
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
	{
		//for (auto it = ways.begin(); it != ways.end(); it++)
		//	if (map.acted[(pos + it->second).x][(pos + it->second).y] != 1) пофиксить этот момент, чтобы если мага убили, он потом не ходил
		//		map[pos + it->second]->Action(map); 
		Move(map);
	}
	map.acted[pos.x][pos.y] = 1;
}