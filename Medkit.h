#pragma once
#include "Actor.h"

class Medkit : public Actor
{
public:
	Medkit(Point& position); //vzaimodeistvie
	char Symbol();
	int Heal();
	void Action(Map&) {};
};