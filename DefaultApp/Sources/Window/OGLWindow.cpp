#include "OGLWindow.h"

#include <algorithm>
#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "LowLevel_Renderer/Cameras/Camera.h"

OGLWindow::OGLWindow(int width, int height, const std::string& title)
	: m_width(width), m_height(height), m_title(title), m_windowOpenGL(nullptr)
{
	//glfwSetInputMode(m_windowOpenGL, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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

	Math::Vector3D<float> movement = { 0.f, 0.f, 0.f };
	
	if (glfwGetKey(m_windowOpenGL, GLFW_KEY_W) == GLFW_PRESS)
		movement.z -= cameraSpeed * 1.f;
	if (glfwGetKey(m_windowOpenGL, GLFW_KEY_S) == GLFW_PRESS)
		movement.z += cameraSpeed * 1.f;
	if (glfwGetKey(m_windowOpenGL, GLFW_KEY_A) == GLFW_PRESS)
		movement.x -= cameraSpeed * 1.f;
	if (glfwGetKey(m_windowOpenGL, GLFW_KEY_D) == GLFW_PRESS)
		movement.x += cameraSpeed * 1.f;
	if (glfwGetKey(m_windowOpenGL, GLFW_KEY_Q) == GLFW_PRESS)
		movement.y -= cameraSpeed * 1.f;
	if (glfwGetKey(m_windowOpenGL, GLFW_KEY_E) == GLFW_PRESS)
		movement.y += cameraSpeed * 1.f;
	
	if (FreeCamMode())
	{
		double xpos, ypos;
		glfwGetCursorPos(m_windowOpenGL, &xpos, &ypos);
		
		float dx = xpos - m_width / 2;
		float dy = ypos - m_height / 2;
		glfwSetCursorPos(m_windowOpenGL, m_width / 2, m_height / 2);
		
		cam.transform.rotation.y -= dx * cameraRotationSpeed;
		cam.transform.rotation.x += dy * cameraRotationSpeed;
	}

	Math::Mat4<float> rotationMat = Math::Mat4<float>::rotation(cam.transform.rotation);
	Math::Vector3D<float> worldMovement = rotationMat * (movement * sensitivity);
	cam.transform.position = cam.transform.position + worldMovement;

	//----TOGGLE CAM MODE----//
	static int oldState = GLFW_PRESS;
	int newState = glfwGetMouseButton(m_windowOpenGL, GLFW_MOUSE_BUTTON_RIGHT);
	if (newState == GLFW_PRESS && oldState == GLFW_RELEASE)
	{
		std::cout << "Mouse click" << std::endl;
		SwitchCameraMode();
	}
	oldState = newState;

	sensitivityChanged.Broadcast(sensitivity);
	
	glfwSetScrollCallback(m_windowOpenGL, ScrollCallback);
}

void OGLWindow::SwitchCameraMode()
{
	glfwSetInputMode(m_windowOpenGL, GLFW_CURSOR, glfwGetInputMode(m_windowOpenGL, GLFW_CURSOR) == GLFW_CURSOR_NORMAL ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
	glfwSetInputMode(m_windowOpenGL, GLFW_RAW_MOUSE_MOTION, glfwGetInputMode(m_windowOpenGL, GLFW_RAW_MOUSE_MOTION) == GLFW_TRUE ? GLFW_FALSE : GLFW_TRUE);
	glfwSetCursorPos(m_windowOpenGL, m_width / 2, m_height / 2);
	cursorIsHidden = !cursorIsHidden;
}

void OGLWindow::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	sensitivity += yoffset * 0.05f;
	sensitivity = std::clamp(sensitivity, 0.1f, 5.f);
}

bool OGLWindow::FreeCamMode()
{
	return cursorIsHidden;
}

void OGLWindow::Init()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	m_windowOpenGL = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
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
