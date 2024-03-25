// SunvyNeverExist Copyright please don't steal work that isn't yours

#include "Core/BaseApplication.h"

#include <iostream>
#include <memory>

using namespace Lite;

int main()
{
	std::unique_ptr<Application> CurrentApp = std::make_unique<Application>();
	CurrentApp->Run();
};
