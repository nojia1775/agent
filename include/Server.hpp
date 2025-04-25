#pragma once

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <random>
#include "Map.hpp"
#include "Agent.hpp"

class	Server
{
	private:
		Map			_map;
		std::vector<Agent *>	_agents;
		uint8_t			_tick;

	public:
					Server(const std::initializer_list<std::initializer_list<char>>& list);
					~Server(void);
					Server(const Server& server) : _map(server._map), _agents(server._agents), _tick(server._tick) {}

		Server&			operator=(const Server& server);
};