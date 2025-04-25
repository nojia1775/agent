#include "Server.hpp"

Server::Server(const std::initializer_list<std::initializer_list<char>>& list) : _map(list), _tick(0)
{
	for (size_t i = 0 ; i < _map.getHeight() ; i++)
	{
		for (size_t j = 0 ; j < _map.getWidth() ; j++)
		{
			if (_map[i][j] == 'A')
				_agents.push_back(new Agent(j, i));
		}
	}
}

Server::~Server(void)
{
	for (auto& agent : _agents)
		delete agent;
}

Server&	Server::operator=(const Server& server)
{
	if (this != &server)
	{
		_map = server._map;
		_tick = server._tick;
		_agents = server._agents;
	}
	return *this;
}