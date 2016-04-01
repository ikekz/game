#include "Character.h"
#include <iostream>
#include "Fireball.h"
#include "Block.h"

using namespace std;

Block::Block(Point& position) : Actor(position) {}

Wall::Wall(Point& position) : Block(position) {}

Space::Space(Point& position) : Block(position) {}

char Wall::Symbol()
{
	return WALL;
}

char Space::Symbol()
{
	return SPACE;
}

void Space::Collide(Character* src, Map& map)
{
	map.Swap(src, this);
	map.SetActed(src->Pos(), 1);
}

void Space::Collide(Fireball* src, Map& map)
{
	map.Swap(src, this);
	map.SetActed(src->Pos(), 1);
}

void Wall::Collide(Character* src, Map& map)
{
	map.SetActed(src->Pos(), 1);
}

void Wall::Collide(Fireball* src, Map& map)
{
	map.Clear(src->Pos());
	delete src;
}