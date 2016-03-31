#pragma once
#include "Actor.h"

class Block : public Actor
{
public:
	Block(Point& position);
	void Action(Map&) {};
};

class Wall : public Block
{
public:
	void Collide(Character*, Map&);
	void Collide(Fireball*, Map&);
	Wall(Point& position);
	char Symbol();
};

class Space : public Block
{
public:
	void Collide(Character*, Map&);
	void Collide(Fireball*, Map&);
	Space(Point& position);
	char Symbol();
};