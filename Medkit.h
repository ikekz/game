#pragma once
#include "Actor.h"

class Medkit : public Actor
{
public:
	Medkit(Point& position); //vzaimodeistvie
	void Collide(Character*, Map&);
	void Collide(Fireball*, Map&);
	char Symbol();
	int PowerHeal();
	void Action(Map&) {};
	static int Count();
	~Medkit();
private:
	static int count;
};