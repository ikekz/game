#include "Actor.h"
#include <set>
#include <iostream>
#include <iterator>

using namespace std;

Actor::Actor(Point& position) : pos(position) {};

Point Actor::Pos()
{
	return pos;
}