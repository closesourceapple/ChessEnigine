#pragma once
#include "..\Board\Board.h"
#include "..\Movement\Movement.h"

class PlayerTurn
{
public:
	PlayerTurn();
	~PlayerTurn();
	bool IscurrectTurn(const Board& board, const MoveData& moveData);
	void ifMoveSuceed_changeTurn();
	bool GetTurn() const;


private:

	bool whiteTurn;

};

