#pragma once
#include "Actor.h"
#include <vector>

class Spawner : public Actor
{
public:
	virtual ~Spawner() {};
	Spawner(Point& position);
	virtual void Action(Map&);
	virtual void Spawn(Map&) = 0;
	virtual int NeedTime() = 0;
protected:
	int time;
	static std::vector<Point> ways;
};

class Cemetry : public Spawner
{
public:
	virtual ~Cemetry() {};
	int NeedTime();
	Cemetry(Point& position);
	void Spawn(Map&);
};

class Nest : public Spawner
{
public:
	virtual ~Nest() {};
	int NeedTime();
	Nest(Point& position);
	void Spawn(Map&);
};