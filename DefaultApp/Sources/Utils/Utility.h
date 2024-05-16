#pragma once

#include <typeinfo>

template <typename Type>
constexpr const char* type_to_string() { return typeid(Type).name(); }

template <typename... types>
struct container
{
	static inline std::initializer_list<const char*> Names = { type_to_string<types>()... };
};
