#pragma once
#include "Actor.h"

class Fireball : public Actor
{
public:
	void Action(Map& map);
	Fireball(Point& position, Point& way);
	void Collide(Actor*, Map&);
	void Collide(Character*, Map&);
	void Collide(Fireball*, Map&);
	virtual ~Fireball() {};
	char Symbol();
	int Damage();
	static std::map<Point, char>& GetWays();
protected:
	Point way;
	static std::map<Point, char> ways;
};