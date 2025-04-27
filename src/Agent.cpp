#include "../include/Agent.hpp"

void	Agent::setSurrounding(const grid& surrounding)
{
	_surrounding = grid(surrounding.size(), std::vector<char>(surrounding[0].size()));
	for (size_t i = 0 ; i < surrounding.size() ; i++)
		_surrounding[i] = surrounding[i];
}

void	Agent::move(grid& map)
{
	std::vector<size_t> food;
	try
	{
		food = getFood();
		if (_y + food[0] < _y)
			_y--;
		else if (_y + food[0] > _y)
			_y++;
		if (_x + food[1] < _x)
			_x--;
		else if (_x + food[1] > _x)
			_x++;
	}
	catch (...)
	{
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
			{
				mov = -1;
				continue;
			}
			if ((std::find(_walls.begin(), _walls.end(), map[y][x])) != _walls.end())
				mov = -1;
		}
		if (_x != x || _y != y)
		{
			_hunger++;
			if (std::find(_food.begin(), _food.end(), _location) == _food.end())
				map[_y][_x] = _location;
			_x = x;
			_y = y;
			_location = map[_y][_x];
			if (std::find(_slower.begin(), _slower.end(), _location) != _slower.end())
			{
				_speed = 1;
				return;
			}
			else if (_location == 'T')
				_hunger = 0;
			else
				_speed = 2;
		}
	}
}

Agent	*Agent::child(const size_t& mutation)
{
	_age++;
	Agent *child = new Agent(*this);
	if (std::rand() % 100 >= (int)mutation)
		return child;
	int where = std::rand() % 5;
	int mut = std::rand() % 2;
	if (mut == 0)
		mut = -1;
	switch (where)
	{
		case 0:
			child->setTimeChild(child->getTimeChild() + mut);
			break;
		case 1:
			child->setTimeDeath(child->getTimeDeath() + mut);
			break;
		case 2:
			child->setTimeHungry(child->getTimeHungry() + mut);
			break;
		case 3:
			if (mut == -1 && child->getSpeed() == 1)
				break;
			child->setSpeed(child->getSpeed() + mut);
			break;
		case 4:
			if (mut == -1 && child->getView() == 1)
				break;
			child->setView(child->getView() + mut);
			break;
	}
	return child;
}

std::vector<size_t>	Agent::getFood(void) const
{
	size_t i = 0;
	size_t j = 0;
	for ( ; i < _view * 2 + 1 ; i++)
	{
		j = 0;
		for ( ; j < _view * 2 + 1; j++)
		{
			if (std::find(_food.begin(), _food.end(), _surrounding[i][j]) != _food.end())
				return {i - _view, j - _view};
		}
	}
	throw NoFood();
}