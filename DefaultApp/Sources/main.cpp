// SunvyNeverExist Copyright please don't steal work that isn't yours

#include <iostream>
#include <memory>

#include "Core/Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{

	std::unique_ptr<Application> application = std::make_unique<Application>();
	application->Run();

	//glfwInit();

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//GLFWwindow* w = glfwCreateWindow(800, 800, "Ta mere la pute", nullptr, nullptr);
	//if (!w)
	//{
	//	std::cout << "Failed to create GLFW window" << std::endl;
	//	glfwTerminate();
	//	return -1;
	//}

	//glfwMakeContextCurrent(w);

	////Load glad so it configures OpenGL
	//gladLoadGL();
	//glViewport(0, 0, 800, 800);

	//while (!glfwWindowShouldClose(w))
	//{
	//	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT);
	//	glfwSwapBuffers(w);
	//	glfwPollEvents();
	//}

	//glfwDestroyWindow(w);
	//glfwTerminate();
};
