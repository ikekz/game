#include "Point.h"

Point::Point(int x, int y) : x(x), y(y) {};

Point Point::operator+(const Point& src) const
{
	return Point(x + src.x, y + src.y);
}

bool Point::operator>(const Point& src) const
{
	if (x > src.x)
		return 1;
	else if (x == src.x && y > src.y)
		return 1;
	else
		return 0;
}

bool Point::operator<(const Point& src) const
{
	if (x < src.x)
		return 1;
	else if (x == src.x && y < src.y)
		return 1;
	else
		return 0;
}

bool Point::operator==(const Point& src) const
{
	if (x == src.x && y == src.y)
		return 1;
	else
		return 0;
}

bool Point::operator!=(const Point& src) const
{
	if (x == src.x && y == src.y)
		return 0;
	else
		return 1;
}