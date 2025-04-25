#pragma once

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <random>

class Map {};
class Agent {};

class	Server
{
	private:
		Map			_map;
		std::vector<Agent *>	_agents;
		uint8_t			_tick;

	public:
		Server(Map& map, const size_t& nbrAgents) : _map(map)
		{
			std::random_device rd;
			std::srand(rd());
		}
};