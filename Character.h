#pragma once
#include "Point.h"
#include "Map.h"
#include <map>
#include <string>

#define HERO 'H'
#define PRINCESS 'P'
#define ZOMBIE 'Z'
#define DRAGON 'D'

class Monster; 
class Hero;

class Character
{
public:
	Character(int health, int damage, Point& position);
	virtual Point Move(Map& map) = 0;
	virtual char Symbol() = 0;
	virtual void Interaction(Character&) = 0;
	virtual void Interaction(Monster&) = 0;
	virtual void Interaction(Hero&) = 0;
	void SetPos(Point& pos);
	Point Pos();
	void TakeDamage(Character&);
	int Health();
protected:
	int health;
	int damage;
	Point pos;
	std::map<std::string, Point> ways;
};

class Princess : public Character
{
public:
	void Interaction(Character&) {};
	void Interaction(Monster&) {};
	void Interaction(Hero&) {};
	Princess(int x, int y);
	Point Move(Map& map);
	char Symbol();
};

class Hero : public Character
{
public:
	void Interaction(Character&);
	void Interaction(Monster&);
	void Interaction(Hero&) {};
	Hero(int x, int y);
	Point Move(Map& map);
	char Symbol();
};

class Monster : public Character
{
public:
	void Interaction(Character&);
	void Interaction(Monster&) {};
	void Interaction(Hero&);
	Monster(int health, int damage, Point& position);
	Point Move(Map& map);
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
