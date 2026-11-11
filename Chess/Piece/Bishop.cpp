#include "_Piece.h"
#include "../Board/Board.h"
#include "../Movement/Movement.h"
#include "../PathTracing/PathTracing.h"

#include <cstdlib>


bool Bishop::Controller(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace, const MoveHistory& history)
{
	if (this->MoveValid_diagonal(xboardx, xmovedatax))
		if (!pathTrace.ClearPath_Diagonal(xboardx, xmovedatax))
			return true;

	return false;
}

bool Bishop::MoveValid_diagonal(const Board& xboardx, const MoveData& xmovedatax)
{

	int tagretPoint = xboardx.GetPiece(xmovedatax.X_to, xmovedatax.Y_to);
	int dx = abs(xmovedatax.X_from - xmovedatax.X_to);
	int dy = abs(xmovedatax.Y_from - xmovedatax.Y_to);

	if (dx != dy)
		return false;

	if (xmovedatax.X_from == xmovedatax.X_to &&
		xmovedatax.Y_from == xmovedatax.Y_to)
		return false;


	if (xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == 3 || xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == -3)
		if (tagretPoint == 0)
			return true;



	if (xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == -3)
		if (tagretPoint > 0)
			return true;



	if (xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == 3)
		if (tagretPoint < 0)
			return true;


	return false;
}
