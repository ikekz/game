#pragma once
#include "Actor.h"

class Medkit : public Actor
{
public:
	Medkit(Point& position);
	char Symbol();
	int Heal();
};