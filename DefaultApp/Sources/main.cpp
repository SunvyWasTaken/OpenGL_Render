// SunvyNeverExist Copyright please don't steal work that isn't yours

#include <iostream>
#include <memory>

#include "Core/Application.h"

#include "Procedural/PerlinNoise.h"

int main()
{
	SimplePerlinNoise Noise;

	char key;
	bool bContinue = true;

	while (bContinue)
	{
		Noise.GenerateNoise();
		Noise.DebugPrintResult();

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "Continue ? Press : Y if yes" << std::endl;
		std::cin >> key;
		std::cout << std::endl;
		std::cout << "----------------------------------------------------" << std::endl;
		std::cout << std::endl;

		if (key != 'y')
		{
			bContinue = false;
		}
	}


	//std::unique_ptr<Application> application = std::make_unique<Application>();
	//application->Run();
};
