#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

class	Agent
{
	typedef std::vector<std::vector<char>> grid;

	private:
		const size_t		_timeDeath;
		size_t			_x;
		size_t			_y;
		size_t			_life;
		size_t			_stamina;
		size_t			_view;
		size_t			_age;
		size_t			_hunger;
		size_t			_speed;
		grid			_surrounding;
		char			_location;
		std::vector<char>	_walls;

	public:
					Agent(void) : _timeDeath(30), _x(0), _y(0), _life(10), _stamina(10), _view(1), _age(0), _hunger(10), _speed(2), _location('0'), _walls({'1', 'O', 'A'}) {}
					~Agent(void) {}

					Agent(const size_t& x, const size_t& y) : _timeDeath(30), _x(x), _y(y), _life(10), _stamina(10), _view(1), _age(0), _hunger(10), _speed(2), _location('0'), _walls({'1', 'O', 'A'}) {}
					Agent(const Agent& agent) : _timeDeath(agent._timeDeath), _x(agent._x), _y(agent._y), _life(agent._life), _stamina(agent._stamina), _view(agent._view), _age(agent._age), _hunger(agent._hunger), _speed(agent._speed), _location(agent._location), _walls(agent._walls) {}

		const size_t&		getX(void) const { return _x; }
		const size_t&		getY(void) const { return _y; }
		const size_t&		getLife(void) const { return _life; }
		const size_t&		getStamina(void) const { return _stamina; }
		const size_t& 		getView(void) const { return _view; }
		const grid&		getSurrounding(void) const { return _surrounding; }
		const char&		getLocation(void) const { return _location; }
		const size_t&		getSpeed(void) const { return _speed; }
		const size_t&		getAge(void) const { return _age; }
		const size_t&		getTimeDeath(void) const { return _timeDeath; }

		void			setPos(const std::vector<size_t> pos) { _x = pos[0]; _y = pos[1]; }
		void			setLocation(const char& location) { _location = location; }
		void			setSurrounding(const grid& surrounding);
		void			setSpeed(const size_t& speed) { _speed = speed; }

		void			move(const grid& map);
		void			addAge(void) { _age++;}
};