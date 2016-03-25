#include "Point.h"

Point::Point(int x, int y) : x(x), y(y) {};

Point Point::operator+(Point& src)
{
	return Point(x + src.x, y + src.y);
}

bool Point::operator>(Point& src)
{
	if (x > src.x && y > src.y)
		return 1;
	else
		return 0;
}

bool Point::operator<(Point& src)
{
	if (x < src.x && y < src.y)
		return 1;
	else
		return 0;
}

bool Point::operator==(Point& src)
{
	if (x == src.x && y == src.y)
		return 1;
	else
		return 0;
}

bool Point::operator!=(Point& src)
{
	if (x == src.x && y == src.y)
		return 0;
	else
		return 1;
}