#pragma once

#include <functional>
#include <variant>
#include <vector>

template<typename... Types>
struct Overload : public Types...
{
	using Types::operator()...;
};

template<typename... Types>
Overload(Types...)->Overload<Types...>;

template<typename Variant, typename... Matchers>
void CheckVariant(Variant&& variant, Matchers&&... matchers)
{
	std::visit(Overload(std::forward<Matchers>(matchers)...), std::forward<Variant>(variant));
}

template<typename... Args>
class IMultiDelegate;

namespace Connection
{
	namespace State
	{
		struct Managed {};
		struct Scoped {};
		struct Undead {};
	}

	template<typename... Args>
	struct Default
	{
		using signal_t = IMultiDelegate<Args...>;
		using slot_t = std::function<void(Args...)>;
		using state_t = std::variant<State::Managed, State::Scoped, State::Undead>;

		Default(signal_t* signal, const slot_t& slot, const state_t& state)
			: Signal(signal)
			, Slot(slot)
			, State(state)
		{}

		signal_t* Signal;
		slot_t Slot;
		state_t State;
	};

	template<typename... Args>
	class Scoped
	{
	public:

		using connection_t = Default<Args...>;
		using signal_t = typename connection_t::signal_t;
		using slot_t = typename connection_t::slot_t;
		
		friend signal_t;

		~Scoped()
		{
			Disconnect();
		}

	private:
		explicit Scoped(connection_t* connection)
			: m_connection(connection)
		{}

		void Disconnect() const
		{
			if (m_connection)
				m_connection->Signal->Disconnect(m_connection);
		}

		mutable connection_t* m_connection;
	};

	template<typename... Args>
	class Slot
	{
	public:
		using connection_t = Scoped<Args...>;
		using signal_t = typename connection_t::signal_t;
		using slot_t = typename connection_t::slot_t;
		using current_t = Slot<Args...>;

		Slot(signal_t& signal, const slot_t& function)
			: m_semaphore{}
			, m_scopedConnection(signal.ConnectScoped([this, function](Args... args)
				{
					if (m_semaphore.IsEnabled())
						return;

					function(args...);
				}))
		{}

		void block()
		{
			m_semaphore.AddBlocker();
		}

		void unblock()
		{
			m_semaphore.RemoveBlocker();
		}

		auto ScopedBlock()
		{
			struct Tmp
			{
				explicit Tmp(current_t& owner)
					: Owner(owner)
				{
					Owner.block();
				}

				~Tmp()
				{
					Owner.unblock();
				}

				current_t& Owner;
			};

			return Tmp{ *this };
		}

		Slot(const current_t&) = delete;
		Slot(current_t&&) = delete;
		Slot& operator=(const current_t&) = delete;
		Slot& operator=(current_t&&) = delete;

	private:
		class Semaphore
		{
		public:
			Semaphore()
				: m_counter(0)
			{}

			void AddBlocker()
			{
				++m_counter;
			}

			void RemoveBlocker()
			{
				--m_counter;
			}

			bool IsEnabled() const
			{
				return m_counter != 0;
			}

		private:
			size_t m_counter;
		};

		Semaphore m_semaphore;
		connection_t m_scopedConnection;
	};
}

template <typename ...Args>
class IMultiDelegate
{
	using connection_t = Connection::Default<Args...>;
	using func_t = typename connection_t::slot_t;
	using state_t = typename connection_t::state_t;
	using current_t = IMultiDelegate<Args...>;
	using scoped_connection_t = Connection::Scoped<Args...>;
	using slot_connection_t = Connection::Slot<Args...>;

public:

	IMultiDelegate() = default;

	~IMultiDelegate()
	{
		for (auto connection = m_AllSubscibe.rbegin(); connection != m_AllSubscibe.rend(); ++connection)
		{
			CheckVariant((*connection)->State,
				[&](typename Connection::State::Managed)
				{
					delete (*connection);
				},
				[&](typename Connection::State::Scoped)
				{
					(*connection)->State = typename Connection::State::Undead{};
				},
				[&](typename Connection::State::Undead)
				{
					delete (*connection);
				}
			);
		}
	}

	// Lambda
	void Bind(const func_t& function) const
	{
		auto* connection = new connection_t(const_cast<current_t*>(this), function,
			state_t{typename Connection::State::Managed{}});

		m_AllSubscibe.push_back(connection);
	}

	// Object Function
	template <typename Instance>
	void Bind(Instance* obj, void (Instance::* objFunction)(Args...)) const
	{
		auto func = [obj, objFunction](Args... args)
			{
				(obj->*objFunction)(args...);
			};

		Bind(func);
	}

	// Const Object Function
	template <typename Instance>
	void Bind(Instance* obj, void (Instance::* objFunction)(Args...) const) const
	{
		auto func = [obj, objFunction](Args... args)
			{
				(obj->*objFunction)(args...);
			};

		Bind(func);
	}

	// Lambda
	scoped_connection_t BindScoped(const func_t& function) const
	{
		auto* connection = new connection_t(const_cast<current_t*>(this), function,
			state_t{ typename Connection::State::Scoped{} });

		m_AllSubscibe.push_back(connection);

		return scoped_connection_t{connection};
	}

	template<typename Instance>
	scoped_connection_t BindScoped(Instance* obj, void(Instance::* objFunction)(Args...)) const
	{
		auto fn = [obj, objFunction](Args... args)
			{
				(obj->*objFunction)(args...);
			};

		return BindScoped(fn);
	}

	template<typename Instance>
	scoped_connection_t BindScoped(Instance* obj, void(Instance::* objFunction)(Args...) const) const
	{
		auto fn = [obj, objFunction](Args... args)
			{
				(obj->*objFunction)(args...);
			};

		return BindScoped(fn);
	}

	slot_connection_t BindSlot(const func_t& function) const
	{
		return slot_connection_t{ *const_cast<current_t*>(this), function };
	}

	void Disconnect(connection_t* connectionToDisconnect) const
	{
		auto connection = std::find(m_AllSubscibe.begin(), m_AllSubscibe.end(), connectionToDisconnect);
		if (connection == m_AllSubscibe.end())
			throw std::runtime_error("Connection is not bound to the signal");

		CheckVariant(connectionToDisconnect->State,
			[&](typename Connection::State::Managed)
			{
				throw std::runtime_error("Connection is managed");
			},
			[&](typename Connection::State::Scoped)
			{
				m_AllSubscibe.erase(connection);
			},
			[&](typename Connection::State::Undead)
			{
			}
		);

		delete connectionToDisconnect;
		connectionToDisconnect = nullptr;
	}

	void Broadcast(Args... args) const
	{
		for (auto& connection : m_AllSubscibe)
		{
			connection->Slot(args...);
		}
	}

private:
	mutable std::vector<connection_t*> m_AllSubscibe;
};

#ifndef DECLARE_MULTICAST_DELEGATE
#define DECLARE_MULTICAST_DELEGATE(DelegateName, ...) class DelegateName : public IMultiDelegate<__VA_ARGS__> {};
#endif // !DECLARE_MULTICAST_DELEGATE
