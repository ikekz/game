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

class Map;
class Monster; 
class Hero;
class Wall;
class Space;
class Character;
class Fireball;
class Princess;

class Actor
{
public:
	Actor(Point position);
	virtual char Symbol() = 0;
	virtual void Collide(Actor*, Map&) {};
	virtual void Collide(Character*, Map&) {};
	virtual void Collide(Wall*, Map&) {};
	virtual void Collide(Space*, Map&) {};
	virtual void Collide(Fireball*, Map&) {};
	Point Pos();
	void SetPos(Point& pos);
	virtual void Action(Map&) {};
protected:
	Point pos;
};

class Fireball : public Actor
{
public:
	void Action(Map& map);
	Fireball(Point& position, Point& way);
	void Collide(Actor*, Map&);
	void Collide(Character*, Map&);
	void Collide(Fireball*, Map&);
	char Symbol();
	int Damage();
protected:
	Point way;
	static std::map<Point, char> ways;
};

class Wall : public Actor
{
public:
	void Collide(Character*, Map&);
	void Collide(Fireball*, Map&);
	Wall(Point& position);
	char Symbol();
};

class Space : public Actor
{
public:
	void Collide(Character*, Map&);
	void Collide(Fireball*, Map&);
	Space(Point& position);
	char Symbol();
};

class Character : public Actor
{
public:
	Character(Point& position, int health, int damage);
	virtual void Move(Map&) = 0;
	void Collide(Actor*, Map&);
	virtual void Collide(Hero*, Map&) {};
	virtual void Collide(Princess*, Map&) {};
	virtual void Collide(Monster*, Map&) {};
	void Collide(Fireball*, Map&);
	void DealDamage(Character*);
	void TakeDamage(int damage);
	int Health();
	void Action(Map& map);
protected:
	int health;
	int damage;
	static std::map<std::string, Point> ways;
};

class Princess : public Character
{
public:
	void Collide(Actor*, Map&);
	void Collide(Character*, Map&);
	Princess(int x, int y);
	void Action(Map& map) {};
	void Move(Map& map) {};
	char Symbol();
};

class Hero : public Character
{
public:
	void Collide(Actor*, Map&);
	void Collide(Character*, Map&);
	void Collide(Monster*, Map&);
	void Collide(Princess*, Map&);
	Hero(int x, int y);
	void Move(Map&);
	char Symbol();
};

class Monster : public Character
{
public:
	void Collide(Actor*, Map&);
	void Collide(Character*, Map&);
	void Collide(Hero*, Map&);
	void Collide(Monster*, Map&);
	Monster(Point& position, int health, int damage);
	void Move(Map&);
	Point SelectWay();
	Point step; //переназвать
};

class Zombie : public Monster
{
public:
	Zombie(int x, int y);
	char Symbol();
};

class Dragon : public Monster
{
public:
	Dragon(int x, int y);
	char Symbol();
};

class Wizard : public Monster
{
public:
	Fireball* CreateFireball(Point& way, Map&);
	char Symbol();
	Wizard(int x, int y);
	void Action(Map&);
};
