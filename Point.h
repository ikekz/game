#pragma once

class Point
{
public:
	int x, y;
	Point(int x = 0, int y = 0);
	Point operator+(const Point&) const;
	bool operator>(const Point&) const;
	bool operator<(const Point&) const;
	bool operator==(const Point&) const;
	bool operator!=(const Point&) const;
};