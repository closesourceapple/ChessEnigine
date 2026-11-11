#pragma once

class Window;
typedef struct  GLFWwindow GLFWwindow;

class Input
{
public:
	static void SetWindow(Window* window);

	static bool IsKeyPressed(int key);
	static bool IsKeyReleased(int key);
	static bool IsMouseButtonPressed(int button);

	static float GetMouseX();
	static float GetMouseY();

	static void HideCursor();
	static void ShowCursor();
	static void LockCursor();


private:\
	static Window* s_Window;
};

































//#include <string>

//class Renderer;
//
//struct Input
//{
//	std::string FromPos_;
//	std::string ToPos_;
//
//
//	Input GetInput();
//	void setInput();
//
//	const char* GetTo() const;
//	const char* GetFrom() const;
//
//
//};