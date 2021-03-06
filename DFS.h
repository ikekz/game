#pragma once

bool DFS(char** buf, int size, int x, int y)
{
	if (x == 1 && y == size - 2)
		return 1;
	else if (buf[x][y] != '#')
	{
		buf[x][y] = '#';
		bool b = 0;
		b = DFS(buf, size, x + 1, y);
		if (!b)
			b = DFS(buf, size, x - 1, y);
		if (!b)
			b = DFS(buf, size, x, y - 1);
		if (!b)
			b = DFS(buf, size, x, y + 1);
		return b;
	}
	return 0;
}