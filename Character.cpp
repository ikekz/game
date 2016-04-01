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

void Character::Heal(int src)
{
	health += src;
	if (health > MaxHealth())
		health = MaxHealth();
}

void Character::Action(Map& map)
{
	Move(map);
	//map.acted[pos.x][pos.y] = 1;
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
	TakeDamage(src->Damage()); // ������� ����� ��� ����� ���������� �������� � ��������
	map.acted[pos.x][pos.y] = 1;
	if (Health() <= 0)
		map.Clear(pos);
	map.Clear(src->Pos());
	//map.Swap(map[src->Pos()], map[pos]);
}

Princess::Princess(int x, int y) : Character(Point(x, y), MaxHealth(), 0) {}

int Princess::MaxHealth()
{
	return 0;
}

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

Hero::Hero(int x, int y) : Character(Point(x, y), MaxHealth(), 50) {}

int Hero::MaxHealth()
{
	return 5000;
}

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
	map.acted[pos.x][pos.y] = 1;
}

void Hero::Collide(Princess* src, Map& map)
{
	map.acted[pos.x][pos.y] = 1;
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

void Monster::Move(Map& map)
{
	set<char> peace = { SPACE, MEDKIT, HERO};
	std::map<string, Point>::iterator it = ways.begin();
	advance(it, rand() % ways.size());
	for (int i = 0; i < ways.size(); it++, it = it == ways.end() ? ways.begin() : it, i++)
		if (peace.find(map[pos + it->second]->Symbol()) != peace.end())
		{
			Collide(map.map[(pos + it->second).x][(pos + it->second).y], map);
			break;
		}
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
	map.acted[pos.x][pos.y] = 1;
}

void Monster::Collide(Monster* src, Map& map)
{
	Move(map);
}

Zombie::Zombie(int x, int y) : Monster(Point(x, y), MaxHealth(), 50) {}

int Zombie::MaxHealth()
{
	return 50;
}

char Zombie::Symbol()
{
	return ZOMBIE;
}

Dragon::Dragon(int x, int y) : Monster(Point(x, y), MaxHealth(), 150) {}

int Dragon::MaxHealth()
{
	return 100;
}

char Dragon::Symbol()
{
	return DRAGON;
}

Wizard::Wizard(int x, int y) : Monster(Point(x, y), MaxHealth(), 10) {}

int Wizard::MaxHealth()
{
	return 50;
}

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
		for (auto it = ways.begin(); it != ways.end(); it++)
			if (map[pos + it->second]->Symbol() == Fireball::GetWays()[it->second]) 
				map[pos + it->second]->Action(map); 
		Move(map);
	}
	map.acted[pos.x][pos.y] = 1;
}