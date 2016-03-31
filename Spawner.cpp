#include "Spawner.h"
#include "Character.h"

using namespace std;

vector<Point> Spawner::ways = { Point(-1, 0), Point(1, 0), Point(0, -1), Point(0, 1) };

Spawner::Spawner(Point& position) : Actor(position) {}

void Spawner::Action(Map& map)
{
	time++;
	if (time >= NeedTime())
	{
		Spawn(map);
		time = 0;
	}
}

Cemetry::Cemetry(Point& position) : Spawner(position) {}

int Cemetry::NeedTime()
{
	return 5;
}

void Cemetry::Spawn(Map& map)
{
	for (int i = 0; i < ways.size(); i++)
		if (map[pos + ways[i]]->Symbol() == SPACE)
		{
			map.map[(pos + ways[i]).x][(pos + ways[i]).y] = new Zombie((pos + ways[i]).x, (pos + ways[i]).y);
			break;
		}

}

Nest::Nest(Point& position) : Spawner(position) {}

int Cemetry::NeedTime()
{
	return 8;
}

void Nest::Spawn(Map& map)
{
	for (int i = 0; i < ways.size(); i++)
		if (map[pos + ways[i]]->Symbol() == SPACE)
		{
			map.map[(pos + ways[i]).x][(pos + ways[i]).y] = new Dragon((pos + ways[i]).x, (pos + ways[i]).y);
			break;
		}
}