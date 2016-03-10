#include <iostream>
#include "Game.h"

using namespace std;

Game game(10);

int main(int argc, char* argv[])
{
	game.Start();
	/*vector<int> v(10);
	for (int i = 0; i < v.size(); i++)
		v[i] = i;

	for (int i = 0; i < v.size(); i++)
	{
		//v.erase(v.begin() + i);
		//v.erase(v.begin() + i);
		//v.erase(v.begin() + i);
		cout << v[i] << " " << i << endl;
		if (v[i] == 7)
			v.erase(v.begin() + i);
		//if (v[i] == 8)
		//	v.erase(v.begin() + i);
		
	}*/
	return 0;
}