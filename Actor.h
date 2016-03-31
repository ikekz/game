#pragma once
#include "Point.h"
#include <map>
#include <string>
#include <vector>
#include "Map.h"

#define HERO 'H'
#define PRINCESS 'P'
#define ZOMBIE 'Z'
#define DRAGON 'D'
#define WIZARD 'W'
#define WALL '#'
#define SPACE '.'
#define MEDKIT '+'
#define CEMETRY 'C'
#define NEST 'N'

class Map;
class Monster; 
class Hero;
class Block;
class Character;
class Fireball;
class Princess;
class Spawner;

class Actor
{
public:
	Actor(Point position);
	virtual char Symbol() = 0;
	virtual void Collide(Actor*, Map&) {};
	virtual void Collide(Character*, Map&) {};
	virtual void Collide(Block*, Map&) {};
	virtual void Collide(Fireball*, Map&) {};
	virtual void Collide(Spawner*, Map&) {};
	virtual ~Actor() {};
	Point Pos();
	void SetPos(Point& pos);
	virtual void Action(Map&) = 0;
protected:
	Point pos;
};
