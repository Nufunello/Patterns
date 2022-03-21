#pragma once

#include <utility>

#include "type/InterfaceOverrider.hpp"

namespace patterns
{
	template <typename... Implementations>
	class Strategy final
		: public Implementations...
	{
	public:
		template <typename ...Interfaces, typename ...Codes>
		Strategy(std::pair<type::Type<Interfaces>, Codes>... args)
			: type::IO<Interfaces, Codes>{args.second}...
		{}
	};

	template <typename ...Interfaces, typename ...Codes>
	Strategy(std::pair<type::Type<Interfaces>, Codes>...) -> Strategy<type::IO<Interfaces, Codes>...>;
}
