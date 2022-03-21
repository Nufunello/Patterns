#include <iostream>

#include "patterns/Strategy.hpp"
#include "patterns/Decorator.hpp"

#include "interfaces/IEntity.hpp"
#include "interfaces/IMoveable.hpp"

void move(interfaces::IMoveable& move)
{
	move(3,4);
}

void entity(interfaces::IEntity& entity)
{
	std::cout << entity('a', 4.);
}

int main()
{
	auto s1 = patterns::Strategy
	{
		std::pair{type::Type<interfaces::IEntity>{},   [](char, double) -> int  { return 4; }},
		std::pair{type::Type<interfaces::IMoveable>{}, [](short, int)   -> void { std::cout << "Move1"; }}
	};

	auto s2 = patterns::Strategy
	{
		std::pair{type::Type<interfaces::IEntity>{},   [](char, double) -> int  { return 4; }},
		std::pair{type::Type<interfaces::IMoveable>{}, [](short, int)   -> void { std::cout << "Move2"; }}
	};

	move(s1);
	std::cout << std::endl;
	move(s2);
	std::cout << std::endl;
	entity(s1);
	std::cout << std::endl;
	entity(s2);
	std::cout << std::endl;

	auto d1 = std::invoke(patterns::DecoratorFactory<interfaces::IMoveable>{}, [](short, int)   -> void { std::cout << "Decorator1"; }, &s2);
	std::invoke(d1, 1, 1);
}
