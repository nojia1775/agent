#include "../include/Agent.hpp"

void	Agent::setSurrounding(const grid& surrounding)
{
	_surrounding = grid(surrounding.size(), std::vector<char>(surrounding[0].size()));
	for (size_t i = 0 ; i < surrounding.size() ; i++)
		_surrounding[i] = surrounding[i];
}

void	Agent::move(const grid& map)
{
	std::random_device rd;
	std::srand(rd());
	int mov = -1;
	std::vector<std::vector<int>> opts({
		{0, 0},
		{1, 0},
		{0, 1},
		{-1, 0},
		{0, -1},
	});
	size_t x, y;
	while (mov == -1)
	{
		mov = std::rand() % 5;
		x = _x + opts[mov][0];
		y = _y + opts[mov][1];
		if (x > map[0].size() - 1 || y > map.size() - 1)
			mov = -1;
		if ((std::find(_walls.begin(), _walls.end(), map[y][x])) != _walls.end())
			mov = -1;
	}
	if (_x != x && _y != y)
		_location = map[y][x];
	_x = x;
	_y = y;
}