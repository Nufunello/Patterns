#pragma once

#include "type/TypeArray.hpp"

namespace type
{
	struct FunctionArguments
	{
	private:
		template <typename Class, typename Return, typename... Args>
		static auto getArguments(Return (Class::*)(Args...)) -> TypeArray<Return, Args...> { return {}; }
		template <typename Class, typename Return, typename... Args>
		static auto getArguments(Return (Class::*)(Args...) const) -> TypeArray<Return, Args...> { return {}; }
	
	public:
		template <typename T>
		using InvokeOperatorArguments = decltype(getArguments(&T::operator()));
	};
}
