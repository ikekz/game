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
	TakeDamage(src->Damage());
	map.SetActed(pos, 1);
	if (Health() <= 0)
		map.Clear(pos);
	map.Clear(src->Pos());
	delete src;
}

Princess::Princess(int x, int y) : Character(Point(x, y), MaxHealth(), Cfg::GetInstance().PrincessDamage()) {}

int Princess::MaxHealth()
{
	return Cfg::GetInstance().PrincessHealth();
}

char Princess::Symbol()
{
	return Cfg::GetInstance().PrincessSymbol();
}

void Princess::Collide(Character* src, Map& map)
{
	src->Collide(this, map);
}

void Princess::Collide(Fireball* src, Map& map)
{
	map.Clear(src->Pos());
	delete src;
}

void Princess::Collide(Actor* src, Map& map)
{
	src->Collide(this, map);
}

Hero::Hero(int x, int y) : Character(Point(x, y), MaxHealth(), Cfg::GetInstance().KnightDamage()) {}

int Hero::MaxHealth()
{
	return Cfg::GetInstance().KnightHealth();
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
		delete src;
	}
	map.SetActed(pos, 1);
}

void Hero::Collide(Princess* src, Map& map)
{
	map.SetActed(pos, 1);
	SetPos(src->Pos());
}

char Hero::Symbol()
{
	return Cfg::GetInstance().KnightSymbol();
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

	Collide(map[pos + ways[s]], map);
}

Monster::Monster(Point& position, int health, int damage) : Character(position, health, damage) {}

void Monster::Move(Map& map)
{
	set<char> p = { Cfg::GetInstance().SpaceSymbol(), Cfg::GetInstance().MedkitSymbol(), Cfg::GetInstance().KnightSymbol() };
	std::map<string, Point>::iterator it = ways.begin();
	advance(it, rand() % ways.size());
	for (int i = 0; i < ways.size(); it++, it = it == ways.end() ? ways.begin() : it, i++)
		if (p.find(map[pos + it->second]->Symbol()) != p.end())
		{
			Collide(map[pos + it->second], map);
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
	map.SetActed(pos, 1);
}

void Monster::Collide(Monster* src, Map& map)
{
	Move(map);
}

Zombie::Zombie(int x, int y) : Monster(Point(x, y), MaxHealth(), Cfg::GetInstance().ZombieDamage()) {}

int Zombie::MaxHealth()
{
	return Cfg::GetInstance().ZombieHealth();
}

char Zombie::Symbol()
{
	return Cfg::GetInstance().ZombieSymbol();
}

Dragon::Dragon(int x, int y) : Monster(Point(x, y), MaxHealth(), Cfg::GetInstance().DragonDamage()) {}

int Dragon::MaxHealth()
{
	return Cfg::GetInstance().DragonHealth();
}

char Dragon::Symbol()
{
	return Cfg::GetInstance().DragonSymbol();
}

Wizard::Wizard(int x, int y) : Monster(Point(x, y), MaxHealth(), Cfg::GetInstance().WizardDamage()) {}

int Wizard::MaxHealth()
{
	return Cfg::GetInstance().WizardHealth();
}

char Wizard::Symbol()
{
	return Cfg::GetInstance().WizardSymbol();
}

Fireball* Wizard::CreateFireball(Point& way, Map& map)
{
	map.SetActed(pos + way, 1);
	return new Fireball(pos + way, way);
}

void Wizard::Action(Map& map)
{
	Point way = map.CalcWay(pos, map.GetHero()->Pos());
	if ((pos.x == map.GetHero()->Pos().x || pos.y == map.GetHero()->Pos().y) && map[pos + way]->Symbol() == Cfg::GetInstance().SpaceSymbol())
		map.Insert(pos + way, CreateFireball(way, map));
	else
	{
		for (auto it = ways.begin(); it != ways.end(); it++)
			if (map[pos + it->second]->Symbol() == Fireball::GetWays()[it->second]) 
				map[pos + it->second]->Action(map); 
		Move(map);
	}
	map.SetActed(pos, 1);
}