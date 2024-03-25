// SunvyNeverExist Copyright please don't steal work that isn't yours

#pragma once

#include "Core.h"

#include <functional>
#include <utility>
#include <vector>

#define DECLARE_DYNAMIC_MULTICAST_DELEGATE(ObjectName) \
class LITE_API ObjectName##Delegate final\
{ \
	using fn = std::function<void()>; \
public: \
	ObjectName##Delegate() = default; \
	virtual ~ObjectName##Delegate() = default; \
	NONCOPYABLE(ObjectName##Delegate) \
	void Broadcast() \
	{ \
		for(auto& it : FunctionBind)\
		{ \
			it(); \
		} \
	}; \
	void Bind(fn func) \
	{ \
		FunctionBind.push_back(func); \
	}; \
private: \
	std::vector<fn> FunctionBind; \
}; \
using ObjectName = ObjectName##Delegate;

#define AddDynamic(target, function) Bind(std::bind(function, target))
