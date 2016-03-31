#include "Medkit.h"

Medkit::Medkit(Point& position) : Actor(position) {}

char Medkit::Symbol()
{
	return '+';
}

int Medkit::Heal()
{
	return 100;
}