#include "Spawner.h"
#include "Character.h"
#include "Fireball.h"

using namespace std;

vector<Point> Spawner::ways = { Point(-1, 0), Point(1, 0), Point(0, -1), Point(0, 1) };

Spawner::Spawner(Point& position) : Actor(position) {}

void Spawner::Collide(Character* src, Map& map)
{
	map.SetActed(src->Pos(), 1);
}

void Spawner::Collide(Fireball* src, Map& map)
{
	map.Clear(src->Pos());
	delete src;
}

void Spawner::Action(Map& map)
{
	map.SetActed(pos, 1);
	time++;
	if (time >= Cooldown())
	{
		Spawn(map);
		time = 0;
	}
}

Cemetry::Cemetry(Point& position) : Spawner(position) {}

int Cemetry::Cooldown()
{
	return 5;
}

void Cemetry::Spawn(Map& map)
{
	for (int i = 0; i < ways.size(); i++)
		if (map[pos + ways[i]]->Symbol() == Cfg::GetInstance().SpaceSymbol())
		{
			map.Insert(pos + ways[i], new Zombie((pos + ways[i]).x, (pos + ways[i]).y));
			break;
		}
}

char Cemetry::Symbol()
{
	return Cfg::GetInstance().CemeterySymbol();
}

Nest::Nest(Point& position) : Spawner(position) {}

int Nest::Cooldown()
{
	return 8;
}

void Nest::Spawn(Map& map)
{
	for (int i = 0; i < ways.size(); i++)
		if (map[pos + ways[i]]->Symbol() == Cfg::GetInstance().SpaceSymbol())
		{
			map.Insert(pos + ways[i], new Dragon((pos + ways[i]).x, (pos + ways[i]).y));
			break;
		}
}

char Nest::Symbol()
{
	return Cfg::GetInstance().NestSymbol();
}