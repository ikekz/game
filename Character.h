#pragma once
#include "Point.h"
#include <map>
#include <string>
#include <vector>

#define HERO 'H'
#define PRINCESS 'P'
#define ZOMBIE 'Z'
#define DRAGON 'D'
#define WIZARD 'W'
#define WALL '#'
#define SPACE '.'

class Monster; 
class Hero;
class Wall;
class Space;
class Character;

class Actor
{
public:
	Actor(Point& position);
	virtual char Symbol() = 0;
	virtual void Collide(Actor&, std::vector<std::vector<Actor*>>& map) = 0;
	virtual void Collide(Monster&, std::vector<std::vector<Actor*>>& map) = 0;
	virtual void Collide(Hero&, std::vector<std::vector<Actor*>>& map) = 0;
	virtual void Collide(Wall&, std::vector<std::vector<Actor*>>& map) = 0;
	virtual void Collide(Space&, std::vector<std::vector<Actor*>>& map) = 0;
	virtual void Collide(Character&, std::vector<std::vector<Actor*>>& map) = 0;
	Point Pos();
	virtual void Action(std::vector<std::vector<Actor*>>& map) = 0;
protected:
	Point pos;
};

class Block : public Actor
{
public:
	void Collide(Actor&, std::vector<std::vector<Actor*>>& map) {};
	void Collide(Monster&, std::vector<std::vector<Actor*>>& map) {};
	void Collide(Hero&, std::vector<std::vector<Actor*>>& map) {};
	void Collide(Wall&, std::vector<std::vector<Actor*>>& map) {};
	void Collide(Space&, std::vector<std::vector<Actor*>>& map) {};
	void Collide(Character&, std::vector<std::vector<Actor*>>& map) {};
	void Action(std::vector<std::vector<Actor*>>& map) {};
	Block(Point& position);
};

class Wall : public Block
{
public:
	void Collide(Monster&, std::vector<std::vector<Actor*>>& map);
	void Collide(Hero&, std::vector<std::vector<Actor*>>& map);
	Wall(Point& position);
	char Symbol();
};

class Space : public Block
{
public:
	void Collide(Monster&, std::vector<std::vector<Actor*>>& map);
	void Collide(Hero&, std::vector<std::vector<Actor*>>& map);
	Space(Point& position);
	char Symbol();
};

class Character : public Actor
{
public:
	Character(Point& position, int health, int damage);
	virtual void Move(std::vector<std::vector<Actor*>>& map) = 0;
	void SetPos(Point& pos);
	void TakeDamage(Character&);
	int Health();
	void Action(std::vector<std::vector<Actor*>>& map);
	void Collide(Actor&, std::vector<std::vector<Actor*>>& map) {};
	void Collide(Monster&, std::vector<std::vector<Actor*>>& map) {};
	void Collide(Hero&, std::vector<std::vector<Actor*>>& map) {};
	void Collide(Wall&, std::vector<std::vector<Actor*>>& map) {};
	void Collide(Space&, std::vector<std::vector<Actor*>>& map) {};
	void Collide(Character&, std::vector<std::vector<Actor*>>& map) {};
protected:
	int health;
	int damage;
	std::map<std::string, Point> ways;
};

class Princess : public Character
{
public:
	void Collide(Monster&, std::vector<std::vector<Actor*>>& map);
	void Collide(Hero&, std::vector<std::vector<Actor*>>& map);
	Princess(int x, int y);
	void Action(std::vector<std::vector<Actor*>>& map) {};
	void Move(std::vector<std::vector<Actor*>>& map) {};
	char Symbol();
};

class Hero : public Character
{
public:
	void Collide(Actor&, std::vector<std::vector<Actor*>>& map);
	void Collide(Monster&, std::vector<std::vector<Actor*>>& map);
	Hero(int x, int y);
	void Move(std::vector<std::vector<Actor*>>& map);
	char Symbol();
};

class Monster : public Character
{
public:
	void Collide(Actor&, std::vector<std::vector<Actor*>>& map);
	void Collide(Hero&, std::vector<std::vector<Actor*>>& map);
	Monster(Point& position, int health, int damage);
	void Move(std::vector<std::vector<Actor*>>& map);
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
	char Symbol();
	Wizard(int x, int y);
	void Move(std::vector<std::vector<Actor*>>& map);
};