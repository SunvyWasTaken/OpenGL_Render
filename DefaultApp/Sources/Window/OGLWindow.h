#pragma once

#include <memory>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Camera;

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
	

private:
	GLFWwindow* m_windowOpenGL;

	int m_width, m_height;
	std::string m_title;

	void _Destroy();

	void SwitchCameraMode();
	bool FreeCamMode();
	
	bool cursorIsHidden = false;
	float cameraSpeed = 0.0025f;
	float cameraRotationSpeed = 0.0005f;
};
