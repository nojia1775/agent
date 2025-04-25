#pragma once

#include <iostream>
#include <vector>

class	Agent
{
	private:
		size_t				_x;
		size_t				_y;
		size_t				_life;
		size_t				_stamina;
		std::vector<std::vector<char>>	_surrounding;

	public:
		Agent(void) : _x(0), _y(0), _life(10), _stamina(10) {}
		~Agent(void) {}

		Agent(const size_t& x, const size_t& y) : _x(x), _y(y), _life(10), _stamina(10) {}
		Agent(const Agent& agent) : _x(agent._x), _y(agent._y), _life(agent._life), _stamina(10) {}

		const size_t&	getX(void) const { return _x; }
		const size_t&	getY(void) const { return _y; }
		const size_t&	getLife(void) const { return _life; }
		const size_t&	getStamina(void) const { return _stamina; }
		void		setPos(const std::vector<const size_t> pos) { _x = pos[0]; _y = pos[1]; }
};