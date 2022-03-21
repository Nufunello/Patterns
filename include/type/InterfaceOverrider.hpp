#pragma once

#include <functional>

#include "type/Type.hpp"
#include "type/FunctionArguments.hpp"

namespace type
{
	template <typename Interface, typename Code, typename Result, typename... Args>
	class InterfaceOverrider
		: public Interface
	{
		Code code;
	public:
		virtual ~InterfaceOverrider() = default;
		template <typename... InterfaceConstructorArgs>
		InterfaceOverrider(Code code, InterfaceConstructorArgs&& ...args) noexcept
			: Interface{std::forward<InterfaceConstructorArgs>(args)...}
			, code{std::move(code)}
		{}
		Result operator()(Args... args) override
		{
			return (std::invoke(code, args...));
		}
	};

	struct InterfaceOverriderFactory
	{
		template <typename Interface, typename Code>
		decltype(auto) operator()(Type<Interface>, Code code) const noexcept
		{
			return typename FunctionArguments::InvokeOperatorArguments<Interface>::PushFront<Code>::PushFront<Interface>::WithT<InterfaceOverrider>{std::move(code)};
		}
	};

	template <typename Interface, typename Code>
	using IO = typename std::invoke_result_t<InterfaceOverriderFactory, Type<Interface>, Code>;
}
