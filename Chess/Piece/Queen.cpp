#include "_Piece.h"
#include "../Board/Board.h"
#include "../Movement/Movement.h"
#include "../PathTracing/PathTracing.h"
#include <cstdlib>




// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //


bool Queen::Controller(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace, const MoveHistory& history)
{
	if (this->MoveValid_vertical(xboardx, xmovedatax) && this->ClearPath_vertical(xboardx, xmovedatax, pathTrace))
		return true;
	if (this->MoveValid_horizontal(xboardx, xmovedatax) && this->ClearPath_horizontal(xboardx, xmovedatax, pathTrace))
		return true;
	if (this->MoveValid_diagonal(xboardx, xmovedatax) && this->ClearPath_diagonal(xboardx, xmovedatax, pathTrace))
		return true;

	return false;
}

//
//

bool Queen::MoveValid_vertical(const Board& xboardx, const MoveData& xmovedatax)
{

	int targetPiece = xboardx.GetPiece(xmovedatax.X_to, xmovedatax.Y_to);

	// samepiececheck
	if (xmovedatax.X_from == xmovedatax.X_to && xmovedatax.Y_from == xmovedatax.Y_to)
		return false;


	if (xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == 5)
	{
		//vertical
		if (xmovedatax.X_from - xmovedatax.X_to == 0)
			if (targetPiece <= 0)
				return true;

	}

	if (xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == -5)
	{
		if (xmovedatax.X_from - xmovedatax.X_to == 0)
			if (targetPiece >= 0)
				return true;

	}


	return false;
}

bool Queen::MoveValid_horizontal(const Board& xboardx, const MoveData& xmovedatax)
{
	int targetPiece = xboardx.GetPiece(xmovedatax.X_to, xmovedatax.Y_to);
	if (xmovedatax.X_from == xmovedatax.X_to && xmovedatax.Y_from == xmovedatax.Y_to)
		return false;

	//horizontal
	if (xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == 5)
		if (xmovedatax.Y_from - xmovedatax.Y_to == 0)
			if (targetPiece <= 0)
				return true;

	if (xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == -5)
	{

		if (xmovedatax.Y_from - xmovedatax.Y_to == 0)
			if (targetPiece >= 0)
				return true;
	}
	return false;
}

bool Queen::MoveValid_diagonal(const Board& xboardx, const MoveData& xmovedatax)
{
	int targetPiece = xboardx.GetPiece(xmovedatax.X_to, xmovedatax.Y_to);
	int dx = abs(xmovedatax.X_from - xmovedatax.X_to);
	int dy = abs(xmovedatax.Y_from - xmovedatax.Y_to);

	if (xmovedatax.X_from == xmovedatax.X_to &&
		xmovedatax.Y_from == xmovedatax.Y_to)
		return false;

	if (!(abs(dx) == abs(dy)))
		return false;


	if (xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == 5 || xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == -5)
		if (targetPiece == 0)
			return true;



	if (xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == -5)
		if (targetPiece > 0)
			return true;



	if (xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == 5)
		if (targetPiece < 0)
			return true;


	return false;
}

bool Queen::ClearPath_vertical(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace)
{

	//vertical
	if (xmovedatax.X_from - xmovedatax.X_to == 0)
		return !pathTrace.ClearPath_Vertical(xboardx, xmovedatax);


	return false;
}

bool Queen::ClearPath_horizontal(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace)
{
	//horizotal
	if (xmovedatax.Y_from - xmovedatax.Y_to == 0)
		return !pathTrace.ClearPath_Horizontal(xboardx, xmovedatax);
	return false;
}

bool Queen::ClearPath_diagonal(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace)
{
	// diagonal
	if ((xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == 5 || xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == -5))
		return !pathTrace.ClearPath_Diagonal(xboardx, xmovedatax);
	return false;
}