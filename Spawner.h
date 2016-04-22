#pragma once
#include "Actor.h"
#include <vector>

class Spawner : public Actor
{
public:
	void Collide(Character*, Map&);
	void Collide(Fireball*, Map&);
	virtual ~Spawner() {};
	Spawner(Point& position);
	virtual void Action(Map&);
	virtual void Spawn(Map&) = 0;
	virtual int Cooldown() = 0;
protected:
	int time = 0;
	static std::vector<Point> ways;
};

class Cemetry : public Spawner
{
public:
	virtual ~Cemetry() {};
	int Cooldown();
	Cemetry(Point& position);
	void Spawn(Map&);
	char Symbol();
};

class Nest : public Spawner
{
public:
	virtual ~Nest() {};
	int Cooldown();
	Nest(Point& position);
	void Spawn(Map&);
	char Symbol();
};