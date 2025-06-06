#include "../include/Map.hpp"

Map::Map(const grid& map) : _height(map.size()), _width(map[0].size())
{
	_map = std::vector<std::vector<char>>(_height, std::vector<char>(_width));
	for (size_t i = 0 ; i < _map.size() ; i++)
		_map[i] = map[i];
}

Map::Map(const std::initializer_list<std::initializer_list<char>>& list) : _height(list.size()), _width(list.begin()->size())
{
	_map = std::vector<std::vector<char>>(_height, std::vector<char>(_width));
	size_t i = 0;
	for (const auto& datas : list)
	{
		size_t j = 0;
		for (const auto& data : datas)
		{
			_map[i][j] = data;
			j++;
		}
		i++;
	}
}

Map::Map(const Map& map) : _height(map._height), _width(map._width)
{
	_map = std::vector<std::vector<char>>(_height, std::vector<char>(_width));
	for (size_t i = 0 ; i < _height ; i++)
	{
		for (size_t j = 0 ; j < _width ; j++)
			_map[i][j] = map._map[i][j];
	}
}

Map&	Map::operator=(const Map& map)
{
	if (this != &map)
	{
		_height = map._height;
		_width = map._width;
		_map = std::vector<std::vector<char>>(_height, std::vector<char>(_width));
		for (size_t i = 0 ; i < _height ; i++)
		{
			for (size_t j = 0 ; j < _width ; j++)
				_map[i][j] = map._map[i][j];
		}
	}
	return *this;
}

std::vector<char>&	Map::operator[](const size_t& index)
{
	if (index > _height - 1)
		throw OutOfRange();
	return _map[index];
}

const std::vector<char>&	Map::operator[](const size_t& index) const
{
	if (index > _height - 1)
		throw OutOfRange();
	return _map[index];
}

std::vector<std::vector<char>>	Map::getSurrounding(const size_t& x, const size_t& y, const size_t& size) const
{
	if (x > _width - 1 || y > _height - 1)
		throw OutOfRange();
	std::vector<std::vector<char>> surrounding(size * 2 + 1, std::vector<char>(size * 2 + 1));
	size_t k = 0;
	for (int i = 0 - size ; i < (int)(size + 1); i++)
	{
		size_t l = 0;
		for (int j = 0 - size; j < (int)(size + 1); j++)
		{
			if (x + j > _width - 1 || y + i > _height - 1)
				surrounding[k][l] = '1';
			else
				surrounding[k][l] = _map[y + i][x + j];
			l++;
		}
		k++;
	}
	return surrounding;
}

const char	*Map::OutOfRange::what(void) const throw() { return "Error: index out of range"; }