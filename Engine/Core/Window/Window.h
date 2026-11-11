#pragma once



typedef struct GLFWwindow GLFWwindow;

class Window
{
public:
	Window(const unsigned int Height, const unsigned int Width, const char* Title);
	~Window();

	void BeginFrame();
	void EndFrame();

	bool ShouldClose();
	bool AnyError() const { return Error; }
	bool IS_GLFW_INIT_() const { return IS_GLFW_INIT; }

	int GetHeight() const { return m_Height; }
	int GetWidth() const { return m_Width; }
	void Close();

	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	GLFWwindow* GetNativeWindow() const { return window; }

private:

	GLFWwindow* window = nullptr;
	bool IS_GLFW_INIT = false;
	bool Error = false;

	int m_Height, m_Width;
};