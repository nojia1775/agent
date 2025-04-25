#pragma once

#include <iostream>
#include <vector>

class	Map
{
	private:
		size_t				_height;
		size_t				_width;
		std::vector<std::vector<char>>	_map;

	public:
						Map(const std::vector<std::vector<char>>& map);
						~Map(void) {}

						Map(const std::initializer_list<std::initializer_list<char>>& list);
						Map(const Map& map);

		Map&				operator=(const Map& map);
		std::vector<char>&		operator[](const size_t& index);

		const size_t&			getHeight(void) const { return _height; }
		const size_t&			getWidth(void) const { return _width; }
		std::vector<std::vector<char>>	getSurrounding(const size_t& x, const size_t& y, const size_t& size) const;
		
		class				OutOfRange : public std::exception { const char *what(void) const throw(); };
};