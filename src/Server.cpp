#include "../include/Server.hpp"

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

Agent	*Server::getAgent(const size_t& index)
{
	if (index > _agents.size() - 1)
		throw OutOfRange();
	return _agents[index];
}

Agent	*Server::getAgent(const size_t& x, const size_t& y)
{
	if (x > _map.getWidth() - 1 || y > _map.getHeight() - 1)
		throw OutOfRange();
	for (auto& agent : _agents)
	{
		if (agent->getX() == x && agent->getY() == y)
			return agent;
	}
	return nullptr;
}

void	Server::setAgentsSurrounding(void)
{
	for (auto& agent : _agents)
		agent->setSurrounding(_map.getSurrounding(*agent));
}

void	Server::play(void)
{
	std::cout << CLEARSCREEN;
	do
	{
		std::cout << REPLACECURSOR;
		display();
		setAgentsSurrounding();
		_tick++;
		for (auto& agent : _agents)
		{
			if (_tick % (10 / agent->getSpeed())== 0)
				agent->move(_map.getMap());
			if (_tick % 10 == 0)
				agent->addAge();
			if (agent->getAge() >= agent->getTimeDeath())
			{
				killAgent(agent);
				break;
			}
		}
		placeAgentsInMap();
		usleep(100000);
	}
	while (_agents.size());
	std::cout << REPLACECURSOR;
	display();
}

void	Server::killAgent(const Agent *agent)
{
	std::vector<Agent *>::iterator it = std::find(_agents.begin(), _agents.end(), agent);
	if (it == _agents.end())
		return;
	delete *it;
	_agents.erase(it);
}

void	Server::placeAgentsInMap(void)
{
	for (size_t i = 0 ; i < _map.getHeight() ; i++)
	{
		for (size_t j = 0 ; j < _map.getWidth() ; j++)
		{
			if (_map[i][j] == 'A')
			{
				Agent *agent = getAgent(j ,i);
				if (!agent)
					_map[i][j] = '0';
				else
					_map[i][j] = agent->getLocation();
			}
		}
	}
	for (const auto& agent : _agents)
	{
		if (agent->getX() > _map.getWidth() - 1 || agent->getY() > _map.getHeight() - 1)
			throw OutOfRange();
		_map[agent->getY()][agent->getX()] = 'A';
	}
}

const char	*Server::OutOfRange::what(void) const throw() { return "Error: index out of range"; }

void	colorfulDisplay(const std::vector<std::vector<char>>& map)
{
	for (const auto& line : map)
	{
		for (const auto& character : line)
		{
			if (character == 'A')
				std::cout << REDB << ' ' << RESET;
			else if (character == '1')
				std::cout << BLACKB << ' ' << RESET;
			else if (character == 'O')
				std::cout << BLUEB << ' ' << RESET;
			else
				std::cout << WHITEB << ' ' << RESET;
		}
		std::cout << std::endl;
	}
}