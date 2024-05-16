#pragma once

#include "Utils/Utility.h"

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

namespace My
{
	template <typename ...Types>
	struct Variant
	{
		using variant_t = typename std::variant<Types...>;
		static inline std::initializer_list<const char*> Names = container<Types...>::Names;
	};

}

//template <typename...Types>
//using Variant_t = My::Variant<Types...>::variant_t;
