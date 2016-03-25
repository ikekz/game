#pragma once

class Point
{
public:
	int x, y;
	Point(int x = 0, int y = 0);
	Point operator+(Point&);
	bool operator>(Point&);
	bool operator<(Point&);
	bool operator==(Point&);
	bool operator!=(Point&);
};