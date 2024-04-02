#pragma once

#include <memory>
#include <string>

class OGLWindow
{
public:
	OGLWindow(int width, int height, const std::string& title);
	~OGLWindow();

	void Init();
	void ClearBackBuffer();
	void SwapBuffer();

	int isWindowShouldClose();
	void PollEvent();

private:
	class GLFWwindow* m_windowOpenGL;

	int m_width, m_height;
	std::string m_title;

	void _Destroy();
};
