#include "_Piece.h"
#include "../Board/Board.h"
#include "../Movement/Movement.h"
#include "../PathTracing/PathTracing.h"





bool Rook::Controller(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace, const MoveHistory& history)
{
	if (this->MoveValid_vertical(xboardx, xmovedatax) && this->ClearPath(xboardx, xmovedatax, pathTrace))
		return true;

	return false;
}

bool Rook::MoveValid_vertical(const Board& xboardx, const MoveData& xmovedatax)
{

	int targetPiece = xboardx.GetPiece(xmovedatax.X_to, xmovedatax.Y_to);

	if (xmovedatax.X_from == xmovedatax.X_to && xmovedatax.Y_from == xmovedatax.Y_to)
		return false;

	if (xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == 4)
	{
		if (xmovedatax.X_from - xmovedatax.X_to == 0)
			if (targetPiece <= 0)
				return true;

		if (xmovedatax.Y_from - xmovedatax.Y_to == 0)
			if (targetPiece <= 0)
				return true;
	}

	if (xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == -4)
	{
		if (xmovedatax.X_from - xmovedatax.X_to == 0)
			if (targetPiece >= 0)
				return true;
		if (xmovedatax.Y_from - xmovedatax.Y_to == 0)
			if (targetPiece >= 0)
				return true;
	}



	return false;
}

bool Rook::ClearPath(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace)
{
	if (xmovedatax.X_from == xmovedatax.X_to)
		return !pathTrace.ClearPath_Vertical(xboardx, xmovedatax);
	if (xmovedatax.Y_from == xmovedatax.Y_to)
		return !pathTrace.ClearPath_Horizontal(xboardx, xmovedatax);

	return false;
}