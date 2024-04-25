#pragma once

#include <any>
#include <functional>
#include <map>

template <typename ...Args>
class IMultiDelegate
{
	using Func = std::function<void(Args...)>;

public:
	// LambdaThings
	void Bind(const Func& function) const
	{
		m_AllSubscibe.insert(std::make_pair(++m_CurrentId, function));
	}

	// WithObject
	template <typename Instance>
	void Bind(Instance* obj, void (Instance::* function)(Args...))
	{
		connect([=](Args... args)
			{
				(obj->*function)(args...);
			});
	}

	template <typename Instance>
	void Bind(Instance* obj, void (Instance::* function)(Args...) const) const
	{
		connect([=](Args... args)
			{
				(obj->*function)(args...);
			});
	}

	void Broadcast(Args... args) const
	{
		for (auto& [id, func] : m_AllSubscibe)
		{
			func(args...);
		}
	}

private:
	mutable std::map<size_t, std::function<void>(std::any anything)> m_AllSubscibe;
	mutable size_t m_CurrentId = 0;
};

#ifndef DECLARE_MULTICAST_DELEGATE
#define DECLARE_MULTICAST_DELEGATE(DelegateName, ...) class DelegateName : public IMultiDelegate<__VA_ARGS__> {};
#endif // !DECLARE_MULTICAST_DELEGATE
