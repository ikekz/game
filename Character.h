#pragma once
#include "Actor.h"

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
	void Heal(int);
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
	void Collide(Fireball*, Map&);
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