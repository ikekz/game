#pragma once
#include <string>
#include "Point.h"
#include <iostream>

#define UP Point(-1, 0)
#define DOWN Point(1, 0)
#define LEFT Point(0, -1)
#define RIGHT Point(0, 1)
#define STOP Point(0, 0)

Point Step()
{
	std::string s;
	std::cin >> s;
	if (s == "up") {
		std::cout << std::endl;
		return UP;
	}
	else if (s == "down") {
		std::cout << std::endl;
		return DOWN;
	}
	else if (s == "left") {
		std::cout << std::endl;
		return LEFT;
	}
	else if (s == "right") {
		std::cout << std::endl;
		return RIGHT;
	}
	else {
		std::cout << "Enter the correct action\n" << std::endl;
		return Step();
	}
	return STOP;
}