#include "OGLWindow.h"

#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "LowLevel_Renderer/Cameras/Camera.h"

OGLWindow::OGLWindow(int width, int height, const std::string& title)
	: m_width(width), m_height(height), m_title(title), m_windowOpenGL(nullptr)
{
}

OGLWindow::~OGLWindow()
{
	_Destroy();
}

void OGLWindow::ClearBackBuffer()
{
	//Clear background color
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	//Clear the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Create new imgui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void OGLWindow::SwapBuffer()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(m_windowOpenGL);
}

int OGLWindow::isWindowShouldClose()
{
	return glfwWindowShouldClose(m_windowOpenGL);
}

void OGLWindow::PollEvent(Camera& cam)
{
	glfwPollEvents();

	const float cameraSpeed = 0.05f; // adjust accordingly
	if (glfwGetKey(m_windowOpenGL, GLFW_KEY_W) == GLFW_PRESS)
		cam.transform.position.z += cameraSpeed * 1.f;
	if (glfwGetKey(m_windowOpenGL, GLFW_KEY_S) == GLFW_PRESS)
		cam.transform.position.z -= cameraSpeed * 1.f;
	if (glfwGetKey(m_windowOpenGL, GLFW_KEY_A) == GLFW_PRESS)
		cam.transform.position.x += cameraSpeed * 1.f;
	if (glfwGetKey(m_windowOpenGL, GLFW_KEY_D) == GLFW_PRESS)
		cam.transform.position.x -= cameraSpeed * 1.f;
	if (glfwGetKey(m_windowOpenGL, GLFW_KEY_SPACE) == GLFW_PRESS)
		cam.transform.position.y += cameraSpeed * 1.f;
	if (glfwGetKey(m_windowOpenGL, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cam.transform.position.y -= cameraSpeed * 1.f;

	double xpos, ypos;
	glfwGetCursorPos(m_windowOpenGL, &xpos, &ypos);
	/*if(xpos > 1)
		cam.transform.rotation.y -= 0.025f * cameraSpeed;
	else if(xpos < -1)
		cam.transform.rotation.y += 0.025f * cameraSpeed;*/

}

void OGLWindow::Init()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_windowOpenGL = glfwCreateWindow(800, 800, m_title.c_str(), nullptr, nullptr);
	if (!m_windowOpenGL)
	{
		std::cout << "Failed to create GLFW window 1" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_windowOpenGL);

	//Load glad so it configures OpenGL
	gladLoadGL();
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, m_width, m_height);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(m_windowOpenGL, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}


void OGLWindow::Draw()
{
}

void OGLWindow::_Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_windowOpenGL);
	glfwTerminate();
}
