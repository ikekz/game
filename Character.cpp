#include "Character.h"
#include "Step.h"
#include <set>

Character::Character(int health, int damage, Point& position) : health(health), damage(damage), pos(position) {}

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
	Point step = Step();
	if (pos + step > Point(-1, -1) && pos + step < Point(map.Size(), map.Size()) &&
		map.Symbol(pos + step) != WALL)
	{
		map.Clear(pos);
		pos = pos + step;
	}
	else
		Move(map);
}

char Hero::Symbol()
{
	return HERO;
}

Monster::Monster(int health, int damage, Point& position) : Character(health, damage, position) {}

void Monster::Move(Map& map)
{
	Point step[4] = { UP, DOWN, LEFT, RIGHT };
	std::set<char> let = { WALL, ZOMBIE, DRAGON, PRINCESS };

	for (int i = rand() % 4, j = 0; j < 4; i = (i + 1) % 4, j++)
		if (pos + step[i] > Point(-1, -1) && pos + step[i] < Point(map.Size(), map.Size()) &&
			let.find(map.Symbol(pos + step[i])) == let.end())
		{
			map.Clear(pos);
			pos = pos + step[i];
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
