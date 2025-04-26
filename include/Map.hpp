#pragma once

#include <iostream>
#include <vector>
#include "Agent.hpp"

class	Map
{
	private:
		typedef std::vector<std::vector<char>> grid;

		size_t			_height;
		size_t			_width;
		grid			_map;

	public:
					Map(const grid& map);
					~Map(void) {}

					Map(const std::initializer_list<std::initializer_list<char>>& list);
					Map(const Map& map);

		Map&			operator=(const Map& map);
		std::vector<char>&	operator[](const size_t& index);

		const size_t&		getHeight(void) const { return _height; }
		const size_t&		getWidth(void) const { return _width; }
		grid			getSurrounding(const size_t& x, const size_t& y, const size_t& size) const;
		grid			getSurrounding(const Agent& agent) const { return getSurrounding(agent.getX(), agent.getY(), agent.getView()); }
		grid			getMap(void) const { return _map; }
		
		class			OutOfRange : public std::exception { const char *what(void) const throw(); };
};