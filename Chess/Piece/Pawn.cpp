#include "_Piece.h"
#include "../Board/Board.h"
#include "../Movement/Movement.h"
#include "../PathTracing/PathTracing.h"
#include "../MoveHistory/MoveHistory.h"

// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //

bool Pawn::Controller(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace, const MoveHistory& history)
{
	if (this->FirstMove(xboardx, xmovedatax, pathTrace))
		return true;
	if (this->MoveValidVertical(xboardx, xmovedatax))
		return true;
	if (this->DiagonalPieceCaputure(xboardx, xmovedatax))
		return true;
	if (this->ENpasant(xboardx, xmovedatax, pathTrace, history))
		return true;

	return false;
}

bool Pawn::MoveValidVertical(const Board& xboardx, const MoveData& xmovedatax)
{
	int pawnpos = xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from);

	if (xboardx.GetPiece(xmovedatax.X_to, xmovedatax.Y_to))
		return false;

	if (pawnpos == 1)
	{

		if (xmovedatax.Y_from - xmovedatax.Y_to == 1 && xmovedatax.X_from == xmovedatax.X_to)
		{
			return true;
		}
	}
	if (pawnpos == -1)
	{


		if (xmovedatax.Y_from - xmovedatax.Y_to == -1 && xmovedatax.X_from == xmovedatax.X_to)
		{
			return true;
		}
	}
	return false
		;
}

bool Pawn::FirstMove(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace)
{
	int pawnpos = xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from);
	int targetPos = xboardx.GetPiece(xmovedatax.X_to, xmovedatax.Y_to);

	if (pawnpos == 1)
		if (xmovedatax.Y_from == 6 && xmovedatax.Y_from - xmovedatax.Y_to == 2 && xmovedatax.X_from == xmovedatax.X_to)
		{
			if (!pathTrace.ClearPath_Vertical(xboardx, xmovedatax) && targetPos == 0)
			{

				return true;
			}
		}


	if (pawnpos == -1)
		if (xmovedatax.Y_from == 1 && xmovedatax.Y_from - xmovedatax.Y_to == -2 && xmovedatax.X_from == xmovedatax.X_to)
		{
			if (!pathTrace.ClearPath_Vertical(xboardx, xmovedatax) && targetPos == 0)
			{
				return true;

			}
		}
	return false;
}



bool Pawn::DiagonalPieceCaputure(const Board& xboardx, const MoveData& xmovedatax)
{
	int targetPiece = xboardx.GetPiece(xmovedatax.X_to, xmovedatax.Y_to);
	int pawnpos = xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from);

	// white piece	
	if (pawnpos == 1)
	{
		if ((xmovedatax.X_from - 1 == xmovedatax.X_to || xmovedatax.X_from + 1 == xmovedatax.X_to)
			&& xmovedatax.Y_from - 1 == xmovedatax.Y_to)
			return targetPiece < 0;
	}

	//black piece
	if (pawnpos == -1)
	{
		if ((xmovedatax.X_from - 1 == xmovedatax.X_to || xmovedatax.X_from + 1 == xmovedatax.X_to)
			&& xmovedatax.Y_from + 1 == xmovedatax.Y_to)
			return targetPiece > 0;
	}


	return false;
}

bool Pawn::ENpasant(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace, const MoveHistory& HisTory)
{


	// enpsant For Black
	if (HisTory.Empty())
		return false;

	if (xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == -1)
	{

		// 2. Get the last move
		MoveHistoryData lastMove = HisTory.Get_LastMove();

		if (xboardx.GetPiece(lastMove.HistoryData.X_to,
			lastMove.HistoryData.Y_to) != 1)
			return false;

		// 3. Was the last move made by a pawn?
		if (!(lastMove.MovedPiece == 1))
			return false;

		// 4. Did that pawn move two squares?
		if (!(lastMove.HistoryData.X_from == lastMove.HistoryData.X_to && lastMove.HistoryData.Y_from == 6 && lastMove.HistoryData.Y_to == 4))
			return false;

		// 5. Is my pawn on the correct rank?
		if (!(xmovedatax.Y_from == 4))
			return false;

		// 6. Is that pawn directly beside mine?
		if (!(lastMove.HistoryData.X_to == xmovedatax.X_from - 1 || lastMove.HistoryData.X_to == xmovedatax.X_from + 1))
			return false;

		// 7. Am I moving one square diagonally?
		if (!(xmovedatax.X_to == lastMove.HistoryData.X_to && xmovedatax.Y_to == lastMove.HistoryData.Y_to + 1))
			return false;

		// 8. Is the destination square empty?
		if ((xboardx.GetPiece(xmovedatax.X_to, xmovedatax.Y_to)))
			return false;

		// 9. Remove the captured pawn
		xboardx.setPiece(lastMove.HistoryData.X_to, lastMove.HistoryData.Y_to, 0);

		return true;

	}
	// for white 



	if (xboardx.GetPiece(xmovedatax.X_from, xmovedatax.Y_from) == 1)
	{


		// 2. Get the last move
		MoveHistoryData lastMove = HisTory.Get_LastMove();


		if (xboardx.GetPiece(lastMove.HistoryData.X_to,
			lastMove.HistoryData.Y_to) != -1)
			return false;

		// 3. Was the last move made by a pawn?
		if (!(lastMove.MovedPiece == -1))
			return false;

		// 4. Did that pawn move two squares?
		if (!(lastMove.HistoryData.X_from == lastMove.HistoryData.X_to && lastMove.HistoryData.Y_from == 1 && lastMove.HistoryData.Y_to == 3))
			return false;

		// 5. Is my pawn on the correct rank?
		if (!(xmovedatax.Y_from == 3))
			return false;

		// 6. Is that pawn directly beside mine?
		if (!(lastMove.HistoryData.X_to == xmovedatax.X_from - 1 || lastMove.HistoryData.X_to == xmovedatax.X_from + 1))
			return false;

		// 7. Am I moving one square diagonally?
		if (!(xmovedatax.X_to == lastMove.HistoryData.X_to && xmovedatax.Y_to == lastMove.HistoryData.Y_to - 1))
			return false;

		// 8. Is the destination square empty?
		if ((xboardx.GetPiece(xmovedatax.X_to, xmovedatax.Y_to)))
			return false;

		// 9. Remove the captured pawn
		xboardx.setPiece(lastMove.HistoryData.X_to, lastMove.HistoryData.Y_to, 0);

		return true;

	}


	return false;
}