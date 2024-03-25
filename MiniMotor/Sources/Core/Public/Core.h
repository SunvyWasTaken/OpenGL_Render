// SunvyNeverExist Copyright please don't steal work that isn't yours

#pragma once

#ifdef LITE_BUILD_DLL
	#define LITE_API __declspec(dllexport)
#else
	#define LITE_API __declspec(dllimport)
#endif // LITE_BUILD_DLL

#define NONCOPYABLE(TypeName) \
	TypeName(TypeName&&) = delete; \
	TypeName(const TypeName&) = delete; \
	TypeName& operator=(const TypeName&) = delete; \
	TypeName& operator=(TypeName&&) = delete;

