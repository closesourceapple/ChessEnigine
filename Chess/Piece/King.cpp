#include "_Piece.h"
#include "../Board/Board.h"
#include "../Movement/Movement.h"
#include "../PathTracing/PathTracing.h"
#include <cstdlib>



// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //

bool King::Controller(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace, const MoveHistory& history)
{
	if (this->MoveValid_(xboardx, xmovedatax))
		return true;
	return false;
}

bool King::MoveValid_(const Board& xboardx, const MoveData& xmovedatax)
{
	if (xmovedatax.X_from == xmovedatax.X_to && xmovedatax.Y_from == xmovedatax.Y_to)
		return false;

	int source = xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from);
	int target = xboardx.GetPiece(xmovedatax.X_to, xmovedatax.Y_to);

	if ((source > 0 && target > 0) ||
		(source < 0 && target < 0))
	{
		return false;
	}



	if (xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == 6)
	{
		if ((abs(xmovedatax.X_from - xmovedatax.X_to) == 1) && (xmovedatax.Y_from == xmovedatax.Y_to))
			return true;


		if (abs(xmovedatax.Y_from - xmovedatax.Y_to) == 1 && (xmovedatax.X_from == xmovedatax.X_to))
			return true;

		if (abs(xmovedatax.X_from - xmovedatax.X_to) == 1 && abs(xmovedatax.Y_from - xmovedatax.Y_to) == 1)
			return true;

	}
	if (xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == -6)
	{
		if ((abs(xmovedatax.X_from - xmovedatax.X_to) == 1) && (xmovedatax.Y_from == xmovedatax.Y_to))
			return true;


		if (abs(xmovedatax.Y_from - xmovedatax.Y_to) == 1 && (xmovedatax.X_from == xmovedatax.X_to))
			return true;

		if (abs(xmovedatax.X_from - xmovedatax.X_to) == 1 && abs(xmovedatax.Y_from - xmovedatax.Y_to) == 1)
			return true;

	}
	return false;
}
