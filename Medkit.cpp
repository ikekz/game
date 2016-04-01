#include "Medkit.h"
#include "Fireball.h"
#include "Character.h"

Medkit::Medkit(Point& position) : Actor(position)
{
	count++;
}

int Medkit::count = 0;

int Medkit::Count()
{
	return count;
}

Medkit::~Medkit()
{
	count--;
}

char Medkit::Symbol()
{
	return MEDKIT;
}

void Medkit::Collide(Character* src, Map& map)
{
	src->Heal(PowerHeal());
	map.Clear(pos);
	map.SetActed(src->Pos(), 1);
	delete this;
}

void Medkit::Collide(Fireball* src, Map& map)
{
	map.Clear(pos);
	map.Clear(src->Pos());
	delete this;
}

int Medkit::PowerHeal()
{
	return 100;
}