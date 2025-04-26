#pragma once

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <random>
#include <algorithm>
#include <unistd.h>
#include "Map.hpp"
#include "Agent.hpp"
#include "Colors.h"

void	colorfulDisplay(const std::vector<std::vector<char>>& map);

class	Server
{
	private:
		typedef std::vector<std::vector<char>> grid;

		Map			_map;
		std::vector<Agent *>	_agents;
		uint8_t			_tick;

	public:
					Server(const std::initializer_list<std::initializer_list<char>>& list);
					~Server(void);
					Server(const Server& server) : _map(server._map), _agents(server._agents), _tick(server._tick) {}

		Server&			operator=(const Server& server);

		size_t			getNbrAgents(void) const { return _agents.size(); }
		uint8_t			getTick(void) const { return _tick; }
		Map&			getMap(void) { return _map; }
		grid			getSurrounding(const Agent& agent) const { return _map.getSurrounding(agent.getX(), agent.getY(), agent.getView()); }
		Agent			*getAgent(const size_t& index);
		Agent			*getAgent(const size_t& x, const size_t& y);

		void			setAgentsSurrounding(void);

		void			display(void) const { colorfulDisplay(_map.getMap()); }
		void			play(void);
		void			killAgent(const Agent *agent);
		void			placeAgentsInMap(void);

		class			OutOfRange : public std::exception { const char *what(void) const throw(); };
};
