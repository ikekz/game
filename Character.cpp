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

char Hero::Symbol()
{
	return HERO;
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

	Collide(*map[(pos + ways[s]).x][(pos + ways[s]).y], map);
}

Block::Block(Point& position) : Actor(position) {}

Wall::Wall(Point& position) : Block(position) {}

Space::Space(Point& position) : Block(position) {}

Monster::Monster(Point& position, int health, int damage) : Character(position, health, damage) {}

void Monster::Move(vector<vector<Actor*>>& map)
{
	if (step.y > 4)
		return;

	std::map<string, Point>::iterator it = ways.begin();
	step.x = (step.x + 1) % ways.size();

	if (step.y == 0)
	{
		step.x = rand() % ways.size();
		step.y++;
	}

	advance(it, step.x);

	Collide(*map[(pos + it->second).x][(pos + it->second).y], map);
	
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

void Space::Collide(Hero& src, std::vector<std::vector<Actor*>>& map)
{
	Point tmp = src.Pos();

	src.SetPos(pos);
	map[pos.x][pos.y] = &src;

	pos = tmp;
	map[pos.x][pos.y] = this;
};

void Space::Collide(Monster& src, std::vector<std::vector<Actor*>>& map)
{
	Point tmp = src.Pos();

	src.SetPos(pos);
	map[pos.x][pos.y] = &src;

	pos = tmp;
	map[pos.x][pos.y] = this;

	src.step.y = 0;

};
void Wall::Collide(Hero& src, std::vector<std::vector<Actor*>>& map)
{
	cout << "Enter the correct action" << endl;
	src.Move(map);
}

void Wall::Collide(Monster& src, std::vector<std::vector<Actor*>>& map)
{
	src.Move(map);
}

void Princess::Collide(Hero& src, std::vector<std::vector<Actor*>>& map)
{
	src.SetPos(pos);
}

void Princess::Collide(Monster& src, std::vector<std::vector<Actor*>>& map)
{
	src.Move(map);
}
