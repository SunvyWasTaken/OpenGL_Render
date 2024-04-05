// SunvyNeverExist Copyright please don't steal work that isn't yours

#include <iostream>
#include <memory>

#include "Core/Application.h"

int main()
{
	std::unique_ptr<Application> application = std::make_unique<Application>();
	application->Run();
};
