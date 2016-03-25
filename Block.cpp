#include "Actor.h"
#include <set>
#include <iostream>
#include <iterator>

using namespace std;

Block::Block(Point& position) : Actor(position) {}

Wall::Wall(Point& position) : Block(position) {}

Space::Space(Point& position) : Block(position) {}

char Wall::Symbol()
{
	return '#';
}

char Space::Symbol()
{
	return '.';
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