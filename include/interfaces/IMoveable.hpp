#pragma once

namespace interfaces
{
	class IMoveable
	{
	protected:
		IMoveable() = default;
		IMoveable(const IMoveable&) = default;
		IMoveable(IMoveable&&) = default;
	public:
		virtual ~IMoveable() = default;
		virtual void operator()(short, int) = 0;
	};
}
