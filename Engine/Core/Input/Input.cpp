#include "Input.h"
#include "../Window/Window.h"

#include <GLFW/glfw3.h>

Window* Input::s_Window = nullptr;

void Input::SetWindow(Window* window)
{
	s_Window = window;
}

bool Input::IsKeyPressed(int key)
{
	int I_AM_Iron_MaN = glfwGetKey(s_Window->GetNativeWindow(), key);
	return I_AM_Iron_MaN == GLFW_PRESS || I_AM_Iron_MaN == GLFW_REPEAT;
}

bool Input::IsKeyReleased(int key)
{
	int I_AM_Iron_MaN_2 = glfwGetKey(s_Window->GetNativeWindow(), key);
	return I_AM_Iron_MaN_2 == GLFW_RELEASE;
}

bool Input::IsMouseButtonPressed(int button)
{
	int m3b54_8la_cy = glfwGetMouseButton(s_Window->GetNativeWindow(), button);
	return m3b54_8la_cy == GLFW_PRESS;

}

float Input::GetMouseX()
{

	double x;
	double y;

	glfwGetCursorPos(s_Window->GetNativeWindow(), &x, &y);
	return (float)x;
}

float Input::GetMouseY()
{
	double x;
	double y;

	glfwGetCursorPos(s_Window->GetNativeWindow(), &x, &y);
	return (float)y;
}

void Input::HideCursor()
{
	glfwSetInputMode(
		s_Window->GetNativeWindow(),
		GLFW_CURSOR,
		GLFW_CURSOR_HIDDEN
	);
}

void Input::ShowCursor()
{
	glfwSetInputMode(
		s_Window->GetNativeWindow(),
		GLFW_CURSOR,
		GLFW_CURSOR_NORMAL
	);
}

void Input::LockCursor()
{
	glfwSetInputMode(
		s_Window->GetNativeWindow(),
		GLFW_CURSOR,
		GLFW_CURSOR_DISABLED
	);
}




























//Input
//├── IsKeyPressed()
//├── IsMouseButtonPressed()
//├── GetMouseX()
//├── GetMouseY()
//├── GetMouseDeltaX()
//├── GetMouseDeltaY()
//├── GetScrollOffset()
//├── HideCursor()
//├── ShowCursor()
//├── LockCursor()
//└── SetWindow()




//#include <iostream>
////Input Input::GetInput()
////{
////	return	*this;
////}
//
//void Input::setInput()
//{
//	std::cout << "Enter Where From Move ->\n";
//	std::cin >> FromPos_;
//	std::cout << "Enter Where To Move ->\n";
//	std::cin >> ToPos_;
//
//}
//
//const char* Input::GetTo() const
//{
//	return	ToPos_.c_str();
//}
//
//const char* Input::GetFrom() const
//{
//	return FromPos_.c_str();
//}