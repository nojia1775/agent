#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

class	Agent
{
	typedef std::vector<std::vector<char>> grid;

	private:
		size_t			_timeDeath;
		size_t			_x;
		size_t			_y;
		size_t			_view;
		size_t			_age;
		size_t			_hunger;
		size_t			_speed;
		char			_location;
		std::vector<char>	_walls;
		std::vector<char>	_slower;
		std::vector<char>	_food;
		size_t			_timeHungry;
		size_t			_timeChild;
		grid			_surrounding;
		
	public:
					Agent(void) : _timeDeath(30), _x(0), _y(0), _view(2), _age(0), _hunger(0), _speed(2), _location('0'), _walls({'1', 'A'}), _slower({'O'}), _food({'T'}), _timeHungry(10), _timeChild(10) {}
					~Agent(void) {}

					Agent(const size_t& x, const size_t& y) : _timeDeath(30), _x(x), _y(y), _view(3), _age(0), _hunger(0), _speed(4), _location('0'), _walls({'1', 'A'}), _slower({'O'}), _food({'T'}), _timeHungry(100), _timeChild(10) {}
					Agent(const Agent& agent) : _timeDeath(agent._timeDeath), _x(agent._x), _y(agent._y), _view(agent._view), _age(0), _hunger(0), _speed(agent._speed), _location(agent._location), _walls(agent._walls), _slower(agent._slower), _food(agent._food), _timeHungry(agent._timeHungry), _timeChild(agent._timeChild) {}

		const size_t&		getX(void) const { return _x; }
		const size_t&		getY(void) const { return _y; }
		const size_t& 		getView(void) const { return _view; }
		const grid&		getSurrounding(void) const { return _surrounding; }
		const char&		getLocation(void) const { return _location; }
		const size_t&		getSpeed(void) const { return _speed; }
		const size_t&		getAge(void) const { return _age; }
		const size_t&		getTimeDeath(void) const { return _timeDeath; }
		const size_t&		getTimeChild(void) const { return _timeChild; }
		const size_t&		getTimeHungry(void) const { return _timeHungry; }
		std::vector<size_t>	getFood(void) const;

		void			setPos(const std::vector<size_t> pos) { _x = pos[0]; _y = pos[1]; }
		void			setLocation(const char& location) { _location = location; }
		void			setSurrounding(const grid& surrounding);
		void			setSpeed(const size_t& speed) { _speed = speed; }
		void			setTimeDeath(const size_t& timeDeath) { _timeDeath = timeDeath; }
		void			setView(const size_t& view) { _view = view; }
		void			setSlower(const std::vector<char>& slower) { _slower = slower; }
		void			setTimeHungry(const size_t& hungry) { _timeHungry = hungry; }
		void			setTimeChild(const size_t& timeChild) { _timeChild = timeChild; }

		void			move(grid& map);
		void			addAge(void) { _age++;}
		bool			isDead(void) const { return _hunger == _timeHungry || _age == _timeDeath; }
		Agent			*child(const size_t& mutation);

		class			NoFood : public std::exception { const char *what(void) const throw() { return "No food"; } };
};