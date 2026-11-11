#pragma once


#include "../../Chess/Movement/Movement.h"
class Window;
class ChessRenderer;

#include<stdint.h>

class ChessInput
{
public:
	ChessInput(Window* window, ChessRenderer* renderer);

	void Update();
	MoveData GetMoveData();
	bool NewMove()const;

	int8_t LastMoves();
	void UpdateWinScreenButtons(int isCheckMatd);

private:
	MoveData m_MoveData;

	ChessRenderer* m_Renderer;
	Window* m_Window;

	bool m_HasSelection = false;
	bool m_LastMousePressed = false;

	bool m_haslnew_move = true;

	bool isFirstMove = true;

	unsigned int m_FromRow;
	unsigned int m_FromColumn;
	unsigned int m_ToRow;
	unsigned int m_ToColumn;

	int8_t m_LastAction = 0;

	unsigned int m_WindowHeight, m_WindowWidth;
	bool m_LastWinScreenMousePressed = false;

};
//Black wins screen
//829 × 777 px
//
//Button	Left, Top	Width × Height
//New Game(74, 639)	321 × 108 px
//Close Game(443, 639)	324 × 104 px
//
//White wins screen
//834 × 778 px
//
//Button	Left, Top	Width × Height
//New Game(77, 641)	321 × 108 px
//Close Game(446, 641)	324 × 104 px