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

namespace My
{
	template <typename ...Types>
	struct Variant
	{
		using variant_t = typename std::variant<Types...>;
	};

	template <typename T, typename ...Types>
	struct Variant<T, Types...>
	{
	public:
		using variant_t = typename std::variant<T, Types...>;

		static std::vector<std::string> GetTypeNames() {
			std::vector<std::string> names;
			std::vector<std::string> TypeRest = Variant<Types...>::GetTypeNames();
			names.push_back(GetName());
			names.insert(names.end(), TypeRest.begin(), TypeRest.end());
			return names;
		}

	private:
		static std::string GetName()
		{
			const std::string fullTypeName = typeid(T).name();
			size_t pos = fullTypeName.find("class ");
			if (pos != std::string::npos)
				return fullTypeName.substr(pos + sizeof("class ") - 1);

			else
				return fullTypeName;
		}
	};

	template <typename T>
	struct Variant<T>
	{
		static std::vector<std::string> GetTypeNames()
		{
			std::vector<std::string> names;
			names.push_back(GetName());
			return names;
		}
	private:
		static std::string GetName()
		{
			const std::string fullTypeName = typeid(T).name();
			size_t pos = fullTypeName.find("class ");
			if (pos != std::string::npos)
				return fullTypeName.substr(pos + sizeof("class ") - 1);

			else
				return fullTypeName;
		}
	};
}