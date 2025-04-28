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
		colorfulDisplay(_agents[0]->getSurrounding());
		_tick++;
		for (size_t i = 0 ; i < _agents.size() ; i++)
		{
			if (_tick % (10 / _agents[i]->getSpeed()) == 0)
				_agents[i]->move(_map.getMap());
			if (_tick % 10 == 0)
				_agents[i]->addAge();
			if (_agents[i]->getAge() == _agents[i]->getTimeChild())
			{
				_agents.push_back(_agents[i]->child(20));
				setAgentsSurrounding();
			}
			if (_agents[i]->isDead())
			{
				killAgent(_agents[i]);
				i--;
			}
		}
		if (_tick % 20 == 0)
			createTree(30);
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
				std::cout << BLACKB << ' ' << RESET;
			else if (character == 'O')
				std::cout << BLUEB << ' ' << RESET;
			else if (character == 'T')
				std::cout << MAGB << ' ' << RESET;
			else
				std::cout << GREENB << ' ' << RESET;
		}
		std::cout << std::endl;
	}
}

static bool	canGrowTree(const Map& map, const size_t& i, const size_t& j)
{
	if (i - 1 < map.getHeight() - 1 && j < map.getWidth() - 1)
	{
		if (map[i - 1][j] == 'O' || map[i - 1][j] == 'T')
			return true;
	}
	if (i + 1 < map.getHeight() - 1 && j < map.getWidth() - 1)
	{
		if (map[i + 1][j] == 'O' || map[i + 1][j] == 'T')
			return true;
	}
	if (i < map.getHeight() - 1 && j - 1 < map.getWidth() - 1)
	{
		if (map[i][j - 1] == 'O' || map[i][j - 1] == 'T')
			return true;
	}
	if (i < map.getHeight() - 1 && j + 1 < map.getWidth() - 1)
	{
		if (map[i][j + 1] == 'O' || map[i][j + 1] == 'T')
			return true;
	}
	return false;
}

void	Server::createTree(const int& percent)
{
	for (size_t i = std::rand() % _map.getHeight() ; i < _map.getHeight() ; i++)
	{
		for (size_t j = std::rand() % _map.getWidth() ; j < _map.getWidth() ; j++)
		{
			if (_map[i][j] == '0')
			{
				if (canGrowTree(_map, i, j))
				{
					int grow = std::rand() % 100;
					if (grow < percent)
					{
						_map[i][j] = 'T';
						return;
					}
				}
			}
		}
	}
}