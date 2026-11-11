#include"_Piece.h"
#include "../Board/Board.h"
#include "../Movement/Movement.h"
#include "../PathTracing/PathTracing.h"
#include <cstdlib>


bool Knight::Controller(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace, const MoveHistory& history)
{
	if (this->MoveValid_vertical(xboardx, xmovedatax))
	{
		return true;
	}
	return false;
}


bool Knight::MoveValid_vertical(const Board& xboardx, const MoveData& xmovedatax)
{
	int dx = abs(xmovedatax.X_from - xmovedatax.X_to);
	int dy = abs(xmovedatax.Y_from - xmovedatax.Y_to);
	int source = xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from);
	int target = xboardx.GetPiece(xmovedatax.X_to, xmovedatax.Y_to);

	if ((source > 0 && target > 0) ||
		(source < 0 && target < 0))
	{
		return false;
	}

	if (xboardx.GetPiece(xmovedatax.X_to, xmovedatax.Y_to) <= 0)
	{
		if (xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == 2)
		{

			if (dx == 1 && dy == 2 || dx == 2 && dy == 1)
			{
				return true;
			}
		}
	}
	if (xboardx.GetPiece(xmovedatax.X_to, xmovedatax.Y_to) >= 0)
	{
		if (xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == -2)
		{

			if (dx == 1 && dy == 2 || dx == 2 && dy == 1)
			{
				return true;
			}
		}
	}

	return false;
}