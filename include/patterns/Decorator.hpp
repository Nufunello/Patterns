#pragma once

#include "type/FunctionArguments.hpp"
#include "type/Type.hpp"
#include "type/FunctionArguments.hpp"

namespace patterns
{
	template <typename Interface, typename Result, typename... Args>
	struct Decorator
		: public Interface
	{
		Interface *child;

		Decorator()
			: child{nullptr}
		{}
		Decorator(Interface* child)
			: child{child}
		{}

		virtual Result operator()(Args ...args) override
		{
			if (child)
			{
				return std::invoke(*child, args...);
			}
			else
			{
				if constexpr (!std::is_same_v<Result, void>)
				{
					return Result{};
				}
			}
		}
	};

	template <typename Code, typename Interface, typename Result, typename... Args>
	struct DecoratorOverrider
		: public Decorator<Interface, Result, Args...>
	{
		Code code;

		template <typename... DecoratorArgs>
		DecoratorOverrider(Code code, DecoratorArgs&& ...args)
			: Decorator<Interface, Result, Args...>{std::forward<DecoratorArgs>(args)...}
			, code{std::move(code)}
		{}

		Result operator()(Args ...args) final
		{
			Decorator<Interface, Result, Args...>::operator()(args...);
			return std::invoke(code, args...);
		}
	};
	

	template <typename Interface>
	struct DecoratorFactory
	{
		template <typename Code, typename... DecoratorArgs>
		decltype(auto) operator()(Code code, DecoratorArgs&& ...args) const noexcept
		{
			using Arguments = typename type::FunctionArguments::InvokeOperatorArguments<Interface>;
			return typename Arguments::PushFront<Interface>::PushFront<Code>::WithT<DecoratorOverrider>{std::move(code), std::forward<DecoratorArgs>(args)...};
		}
	};
}
