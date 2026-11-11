#include "PlayerTurn.h"

PlayerTurn::PlayerTurn() : whiteTurn(true) {}
PlayerTurn::~PlayerTurn() {}

bool PlayerTurn::IscurrectTurn(const Board& board, const MoveData& moveData)
{

	int piece = board.GetPiece(moveData.X_from, moveData.Y_from);
	if (whiteTurn == true && piece > 0)
	{

		return true;

	}
	else if (whiteTurn == false && piece < 0)
	{

		return true;
	}
	else
	{
		return false;
	}
}


void PlayerTurn::ifMoveSuceed_changeTurn()
{

	whiteTurn = !whiteTurn;

}

bool PlayerTurn::GetTurn() const
{
	return whiteTurn;
}
