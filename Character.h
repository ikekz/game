#pragma once
#include "Point.h"
#include "Map.h"

#define HERO 'h'
#define PRINCESS 'p'
#define ZOMBIE 'z'
#define DRAGON 'd'

class Character
{
public:
	Character(int health, int damage, Point& position);
	virtual void Move(Map& map) = 0;
	virtual char Symbol() = 0;
	Point Pos();
	bool Fight(Character&);
	void TakeDamage(Character&);
	void DealDamage(Character&);
	int Health();
protected:
	int health;
	int damage;
	Point pos;
};

class Princess : public Character
{
public:
	Princess(int x, int y);
	void Move(Map& map);
	char Symbol();
};

class Hero : public Character
{
public:
	Hero(int x, int y);
	void Move(Map& map);
	char Symbol();
};

class Monster : public Character
{
public:
	Monster(int health, int damage, Point& position);
	void Move(Map& map);
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
