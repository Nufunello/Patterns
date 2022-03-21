#pragma once

namespace interfaces
{
	class IEntity
	{
	protected:
		IEntity() = default;
		IEntity(const IEntity&) = default;
		IEntity(IEntity&&) = default;
	public:
		virtual ~IEntity() = default;
		virtual int operator()(char, double) = 0;
	};
}
