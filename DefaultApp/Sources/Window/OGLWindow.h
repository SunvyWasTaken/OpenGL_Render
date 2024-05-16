#pragma once

#include <memory>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Editor/Observer/SignalSlot.h"
class Camera;

DECLARE_MULTICAST_DELEGATE(OnChangeSensitivity, float)

class OGLWindow
{
public:
	OGLWindow(int width, int height, const std::string& title);
	~OGLWindow();

	void Init();
	void ClearBackBuffer();
	void SwapBuffer();

	int isWindowShouldClose();
	void Draw();
	void PollEvent(Camera& cam);

	OnChangeSensitivity sensitivityChanged;
	void ToggleCameraRotationMode();

private:
	GLFWwindow* m_windowOpenGL;

	int m_width, m_height;
	std::string m_title;

	void _Destroy();

	void SwitchCameraMode();
	bool FreeCamMode();
	
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	bool toggleModeEnabled = false;
	bool cursorIsHidden = false;
	float cameraSpeed = 0.05f;
	float cameraRotationSpeed = 0.0005f;
	static inline float sensitivity = 0.5f;
};
