#pragma once
#include <vector>
#include "Point.h"

#define WALL '#'
#define SPACE '.'

class Actor;

class Map
{
public:
	Map(int size);
	void GenMap();
	void RenderMap();
	int Size();
	Actor* operator[](const Point&);
	bool CheckWay(char** buf, int x, int y);
	void Swap(Actor*, Actor*);
	void PlaceHeroes();
	void Clear(Point&);
	Point CalcWay(Point&, Point&);
	void RefreshActed();
	Actor* GetHero();
	Actor* GetPrincess();
	void SetActed(Point&, bool);
	void Insert(Point&, Actor*);
	bool IsActed(Point&);
	//Actor* GetActor(Point&);
private:
	std::vector<std::vector<Actor*>> map;
	std::vector<std::vector<bool>> acted;
	Actor* hero;
	Actor* princess;
};
