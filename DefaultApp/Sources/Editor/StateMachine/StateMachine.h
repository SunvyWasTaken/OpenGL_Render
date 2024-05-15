#pragma once

#include <string>
#include <typeinfo>
#include <variant>
#include <vector>

template<typename... Types>
struct Overload : public Types...
{
	using Types::operator()...;
};

template<typename... Types>
Overload(Types...) -> Overload<Types...>;

template<typename Variant, typename... Matchers>
void CheckVariant(Variant&& variant, Matchers&&... matchers)
{
	std::visit(Overload(std::forward<Matchers>(matchers)...), std::forward<Variant>(variant));
}

// I know typeid depends on compiler and not garanted but i wanted to retrive the name
// And not depend on a var from a parent class or define on each class.
// I also wanted to tried something with template
template <typename Type>
constexpr const char* type_to_string() { return typeid(Type).name(); }

namespace My
{
	template <typename ...Types>
	struct Variant
	{
		using variant_t = typename std::variant<Types...>;
		static inline std::initializer_list<const char*> Names = { type_to_string<Types>()... };
	};

	template <typename Type>
	struct getFirst
	{};

	template <typename T, typename... Types>
	struct getFirst<Variant<T, Types...>>
	{
		using value = T;
	};

	template <typename Type>
	struct PopFront
	{};

	template <typename T, typename ...Types>
	struct PopFront<Variant<T, Types...>>
	{
		using value = Variant<Types...>;
	};

	template <typename T>
	using PopFront_v = typename PopFront<T>::value;

	template <unsigned int index, typename Type>
	struct getAt : getAt<index - 1, PopFront_v<Type>>
	{};

	template <typename Type>
	struct getAt<0, Type> : getFirst<Type>
	{};
}

template <unsigned int index, typename Types>
using getAt_v = typename My::getAt<index, Types>::value;

//template <typename...Types>
//using Variant_t = My::Variant<Types...>::variant_t;
