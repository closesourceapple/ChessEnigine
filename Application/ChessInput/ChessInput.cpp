#include "ChessInput.h"
#include "../ChessRenderer/ChessRenderer.h"

#include "../../Engine/Core/Input/Input.h"
#include "../../Engine/Core/Window/Window.h"
#include <GLFW/glfw3.h>

ChessInput::ChessInput(Window* window, ChessRenderer* renderer)
{
	Input::SetWindow(window);
	m_Window = window;
	m_Renderer = renderer;
}

void ChessInput::Update()
{
	m_haslnew_move = false;
	float mouseX = Input::GetMouseX();
	float mouseY = Input::GetMouseY();
	float boardX = m_Renderer->GetBoardX();
	float boardY = m_Renderer->GetBoardY();
	float squareSize = m_Renderer->GetSquareSize();


	m_WindowHeight = m_Window->GetHeight();
	m_WindowWidth = m_Window->GetWidth();

	bool mousePressed =
		Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT);

	bool mouseClicked =
		mousePressed && !m_LastMousePressed;


	if (mouseX >= boardX && mouseX < boardX + squareSize * 8 &&
		mouseY >= boardY && mouseY < boardY + squareSize * 8)
	{
		if (mouseClicked)
		{
			if (isFirstMove)
			{
				m_FromColumn = (mouseX - boardX) / squareSize;
				m_FromRow = (mouseY - boardY) / squareSize;
				isFirstMove = false;

				m_MoveData.X_from = 0;

				m_MoveData.X_to = 0;

				m_MoveData.Y_from = 0;
				m_MoveData.Y_to = 0;




			}
			else
			{

				m_ToColumn = (mouseX - boardX) / squareSize;
				m_ToRow = (mouseY - boardY) / squareSize;



				m_MoveData.X_from = m_FromColumn;
				m_MoveData.X_to = m_ToColumn;

				m_MoveData.Y_from = m_FromRow;
				m_MoveData.Y_to = m_ToRow;



				isFirstMove = true;

				m_haslnew_move = true;   // ⭐ THIS IS THE IMPORTANT PART



			}


		}
	}

	m_LastMousePressed = mousePressed;

}









MoveData ChessInput::GetMoveData()
{
	return m_MoveData;
}

bool ChessInput::NewMove() const
{
	return m_haslnew_move;
}

int8_t ChessInput::LastMoves()
{

	return m_LastAction;

}

void ChessInput::UpdateWinScreenButtons(int isCheckMatd)
{
	float mouseX = Input::GetMouseX();
	float mouseY = Input::GetMouseY();

	bool mousePressed =
		Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT);
	bool mouseClicked =
		mousePressed && !m_LastWinScreenMousePressed;

	float PopupHeight = m_WindowHeight * 0.35;
	float PopupWidth = m_WindowWidth * 0.50;

	float popupX = (m_WindowWidth - PopupWidth) / 2.0f;
	float popupY = (m_WindowHeight - PopupHeight) / 2.0f;

	float NewButtonX = popupX + (77.5f / 829.0f) * PopupWidth;
	float NewButtonY = popupY + (639.0f / 777.0f) * PopupHeight;

	float NewButtonWidth = (396.5f - 77.5f) / 829.0f * PopupWidth;
	float NewButtonHeight = (748.0f - 639.0f) / 777.0f * PopupHeight;

	float CloseButtonX = popupX + (450.5f / 829.0f) * PopupWidth;
	float CloseButtonY = popupY + (639.0f / 777.0f) * PopupHeight;

	float CloseButtonWidth = (768.5f - 450.5f) / 829.0f * PopupWidth;
	float CloseButtonHeight = (744.0f - 639.0f) / 777.0f * PopupHeight;


	if (mouseClicked) {

		if (mouseX >= NewButtonX &&
			mouseX <= NewButtonX + NewButtonWidth &&
			mouseY >= NewButtonY &&
			mouseY <= NewButtonY + NewButtonHeight)
			m_LastAction = 1;



		if (mouseX >= CloseButtonX &&
			mouseX <= CloseButtonX + CloseButtonWidth &&
			mouseY >= CloseButtonY &&
			mouseY <= CloseButtonY + CloseButtonHeight)
			m_LastAction = 2;

	}
	m_LastWinScreenMousePressed = mousePressed;
}







/* chatGPT's try */




//void ChessInput::Update()
//{
//	//std::cout << this << '\n';
//	//std::cout << "Update called\n";
//	float mouseX = Input::GetMouseX();
//	float mouseY = Input::GetMouseY();
//
//	float boardX = m_Renderer->GetBoardX();
//	float boardY = m_Renderer->GetBoardY();
//	float squareSize = m_Renderer->GetSquareSize();
//
//	m_haslnew_move = false;
//
//	bool mousePressed =
//		Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT);
//
//
//	//std::cout
//	//	<< "Mouse = (" << mouseX << "," << mouseY << ") "
//	//	<< "Pressed = " << mousePressed
//	//	<< " Last = " << m_LastMousePressed
//	//	<< " Selected = " << m_HasSelection
//	//	<< std::endl;
//
//	// if true Mouse is Inside the Board
//	if (mouseX >= boardX && mouseX < boardX + squareSize * 8 &&
//		mouseY >= boardY && mouseY < boardY + squareSize * 8)
//	{
//		//std::cout
//		//	<< "Pressed = " << mousePressed
//		//	<< " Last = " << m_LastMousePressed
//		//	<< " Selected = " << m_HasSelection
//		//	<< '\n';
//
//
//		std::cout << "mousePressed = " << mousePressed
//			<< "  last = " << m_LastMousePressed
//			<< "  edge = " << (mousePressed && !m_LastMousePressed)
//			<< '\n';
//		if (mousePressed)
//		{
//			//std::cout << "HasSelection = " << m_HasSelection << '\n';
//			if (!m_HasSelection)
//			{
//
//				if (!m_HasSelection)
//				{
//					std::cout << "FIRST CLICK\n";
//					m_FromRow = (mouseY - boardY) / squareSize;
//					m_FromColumn = (mouseX - boardX) / squareSize;
//
//					m_HasSelection = true;
//					//std::cout << "Selected: "
//					//	<< m_FromColumn << ", "
//					//	<< m_FromRow << '\n';
//				}
//				else
//				{
//
//					std::cout << "SECOND CLICK\n";
//					m_ToColumn = (mouseX - boardX) / squareSize;
//					m_ToRow = (mouseY - boardY) / squareSize;
//
//					m_MoveData.X_from = m_FromColumn;
//					m_MoveData.X_to = m_ToColumn;
//
//					m_MoveData.Y_from = m_FromRow;
//					m_MoveData.Y_to = m_ToRow;
//
//
//					std::cout << "SETTING NEW MOVE TRUE\n";
//					m_HasSelection = false;
//					m_haslnew_move = true;
//					//std::cout << "Destination: "
//					//	<< m_ToColumn << ", "
//					//	<< m_ToRow << '\n';
//
//					//std::cout << "Move Ready!\n";
//
//				}
//			}
//
//		}
		//std::cout
		//	<< "Pressed = " << mousePressed
		//	<< " Last = " << m_LastMousePressed
		//	<< '\n';

		//std::cout << "Before assign: " << m_LastMousePressed << '\n';

//		m_LastMousePressed = mousePressed;
//
//		//std::cout << "After assign : " << m_LastMousePressed << '\n';
//		m_LastMousePressed = mousePressed;
//	}
//}