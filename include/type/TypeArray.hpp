#pragma once

namespace type
{
	template <typename... Args>
	struct TypeArray
	{
		template <typename... Args2>
		using Add = TypeArray<Args..., Args2...>;
		template <template <typename...> typename T>
		using WithT = T<Args...>;
		template <typename T>
		using PushFront = TypeArray<T, Args...>;
	};
}
