#include "SpecialMoves.h"
#include "../../Movement/Movement.h"
#include "../../Board/Board.h"
#include "../../Check/Check.h"
#include "../../MoveHistory/MoveHistory.h"
#include "../../PathTracing/PathTracing.h"


bool SpecialMoves::PromotionCheck(Board& board, const MoveData& moveData, int MovedPiece)
{
	if (MovedPiece == 1)
	{
		if (moveData.Y_to == 0)
		{
			board.setPiece(moveData.X_to, moveData.Y_to, 5);
			return true;
		}
	}

	if (MovedPiece == -1)
	{
		if (moveData.Y_to == 7)
		{
			board.setPiece(moveData.X_to, moveData.Y_to, -5);
			return true;
		}
	}

	return false;
}


bool SpecialMoves::CastlingCheck(
	const Board& board,
	const MoveData& moveData,
	MoveHistory& history,
	PathTrace& trace,
	Check& check)
{



	int kinga = board.GetPiece(
		moveData.X_from,
		moveData.Y_from
	);




	// King must move exactly two squares horizontally
	if (abs(moveData.X_to - moveData.X_from) != 2)
	{
		return false;
	}


	// King must actually be moving
	int kingb = board.GetPiece(
		moveData.X_from,
		moveData.Y_from
	);

	if (kingb != 6 && kingb != -6)
	{
		return false;
	}



	// =========================
	// WHITE CASTLING
	// =========================


	// fixed 

	if (kingb == 6 && moveData.Y_from == 7 && moveData.Y_to == 7)
	{



		// White kingside: e1 -> g1
		if (moveData.X_from == 4 && moveData.X_to == 6)
		{
			// rook must be on h1
			if (board.GetPiece(0, 7) != 4)
				return false;

			// squares f1 and g1 must be empty
			if (board.GetPiece(5, 0) != 0 ||
				board.GetPiece(6, 0) != 0)
				return false;


			MoveData pathMove;

			pathMove.X_from = 7;
			pathMove.Y_from = 0;

			pathMove.X_to = 4;
			pathMove.Y_to = 0;
			if (trace.ClearPath_Horizontal(board, pathMove))
				return false;


			for (int x = moveData.X_from + 1;
				x <= moveData.X_to;
				x++)
			{
				MoveData testMove;





				testMove.X_from = moveData.X_from;
				testMove.Y_from = moveData.Y_from;
				testMove.X_to = x;
				testMove.Y_to = moveData.Y_to;

				bool safe = check.MoveKeepsKingSafe(
					board,
					testMove,
					Team::White,
					history
				);


				if (!safe)
				{

					return false;
				}


				if (!check.MoveKeepsKingSafe(
					board,
					testMove,
					Team::White,
					history))
				{
					return false;
				}
			}




			for (int i = 0; i < history.Size(); i++)
			{
				MoveHistoryData move = history.GetMove(i);

				if (move.MovedPiece == 6)
					return false;

				if (move.MovedPiece == 4 &&
					move.HistoryData.X_from == 7 &&
					move.HistoryData.Y_from == 0)
					return false;
			}

			return true;
		}
		//the white king side is whole corrct and oter are probaly worong 
		// 
		// 
		// White queenside: e1 -> c1
		if (moveData.X_from == 4 && moveData.X_to == 2)
		{
			// rook must be on a1
			if (board.GetPiece(0, 7) != 4)
				return false;

			// squares b1, c1 and d1 must be empty
			if (board.GetPiece(1, 7) != 0 ||
				board.GetPiece(2, 7) != 0 ||
				board.GetPiece(3, 7) != 0)
				return false;



			for (int i = 0; i < history.Size(); i++)
			{
				MoveHistoryData move = history.GetMove(i);

				if (move.MovedPiece == 6)
					return false;

				if (move.MovedPiece == 4 &&
					move.HistoryData.X_from == 0 &&
					move.HistoryData.Y_from == 7)
					return false;
			}


			for (int x = moveData.X_from - 1;
				x >= moveData.X_to;
				x--)
			{
				MoveData testMove;

				testMove.X_from = moveData.X_from;
				testMove.Y_from = moveData.Y_from;
				testMove.X_to = x;
				testMove.Y_to = moveData.Y_to;

				if (!check.MoveKeepsKingSafe(
					board,
					testMove,
					Team::White,
					history))
				{
					return false;
				}
			}

			return true;
		}
	}


	// =========================
	// BLACK CASTLING
	// =========================

	if (kingb == -6 && moveData.Y_from == 0 && moveData.Y_to == 0)
	{
		// Black kingside: e8 -> g8
		if (moveData.X_from == 4 && moveData.X_to == 6)
		{
			// rook must be on h8
			if (board.GetPiece(7, 0) != -4)
				return false;

			// f8 and g8 must be empty
			if (board.GetPiece(5, 0) != 0 ||
				board.GetPiece(6, 0) != 0)
				return false;

			// King must not pass through check
			for (int x = moveData.X_from + 1;
				x <= moveData.X_to;
				x++)
			{
				MoveData testMove;

				testMove.X_from = moveData.X_from;
				testMove.Y_from = moveData.Y_from;

				testMove.X_to = x;
				testMove.Y_to = moveData.Y_to;

				if (!check.MoveKeepsKingSafe(
					board,
					testMove,
					Team::Black,
					history))
				{
					return false;
				}
			}

			// King and rook must never have moved
			for (int i = 0; i < history.Size(); i++)
			{
				MoveHistoryData move = history.GetMove(i);

				if (move.MovedPiece == -6)
					return false;

				if (move.MovedPiece == -4 &&
					move.HistoryData.X_from == 7 &&
					move.HistoryData.Y_from == 0)
					return false;
			}

			return true;
		}


		// Black queenside: e8 -> c8
		if (moveData.X_from == 4 && moveData.X_to == 2)
		{
			// rook must be on a8
			if (board.GetPiece(0, 0) != -4)
				return false;

			// b8, c8 and d8 must be empty
			if (board.GetPiece(1, 0) != 0 ||
				board.GetPiece(2, 0) != 0 ||
				board.GetPiece(3, 0) != 0)
				return false;

			// King must not pass through check
			for (int x = moveData.X_from - 1;
				x >= moveData.X_to;
				x--)
			{
				MoveData testMove;

				testMove.X_from = moveData.X_from;
				testMove.Y_from = moveData.Y_from;

				testMove.X_to = x;
				testMove.Y_to = moveData.Y_to;

				if (!check.MoveKeepsKingSafe(
					board,
					testMove,
					Team::Black,
					history))
				{
					return false;
				}
			}

			// King and rook must never have moved
			for (int i = 0; i < history.Size(); i++)
			{
				MoveHistoryData move = history.GetMove(i);

				if (move.MovedPiece == -6)
					return false;

				if (move.MovedPiece == -4 &&
					move.HistoryData.X_from == 0 &&
					move.HistoryData.Y_from == 0)
					return false;
			}

			return true;
		}
	}


	return false;
}




void SpecialMoves::ApplyCastling(
	Board& board,
	const MoveData& moveData)
{
	int king = board.GetPiece(
		moveData.X_from,
		moveData.Y_from
	);

	// WHITE
	if (king == 6)
	{
		// White kingside: e1 -> g1
		if (moveData.X_to == 6)
		{
			board.setPiece(5, 7, 4); // rook h1 -> f1
			board.setPiece(7, 7, 0); // remove rook from h1
		}

		// White queenside: e1 -> c1
		else if (moveData.X_to == 2)
		{
			board.setPiece(3, 7, 4); // rook a1 -> d1
			board.setPiece(0, 7, 0); // remove rook from a1
		}
	}

	// BLACK
	else if (king == -6)
	{
		// Black kingside: e8 -> g8
		if (moveData.X_to == 6)
		{
			board.setPiece(5, 0, -4); // rook h8 -> f8
			board.setPiece(7, 0, 0);  // remove rook from h8
		}

		// Black queenside: e8 -> c8
		else if (moveData.X_to == 2)
		{
			board.setPiece(3, 0, -4); // rook a8 -> d8
			board.setPiece(0, 0, 0);  // remove rook from a8
		}
	}
}










// // MY Version
//bool SpecialMoves::CastlingCheck(const Board& board, const MoveData& moveData,
//	MoveHistory& history, PathTrace& trace, Check& check)
//{
//	if (abs(moveData.X_to - moveData.X_from) != 2)
//		return false;
//
//	int king = board.GetPiece(moveData.X_from, moveData.Y_from);
//
//	if (king != 6 || king != -6)
//		return false;
//
//
//
//	if (board.GetPiece(moveData.X_from, moveData.Y_from) == 4
//		|| board.GetPiece(moveData.X_from, moveData.Y_from) == 6)
//	{
//
//		if ((moveData.Y_from == 0 && moveData.Y_to == 0)) // check for vertical movement
//			if ((moveData.X_from == 7 && moveData.X_to == 5) || (moveData.X_from == 4 && moveData.X_to == 6)
//				|| (moveData.X_from == 4 && moveData.X_to == 2) || (moveData.X_from == 0 && moveData.X_to == 3))
//			{
//				for (int i = 0; i < history.Size(); i++)
//				{
//					MoveHistoryData move = history.GetMove(i);
//
//					if (move.MovedPiece == 6)
//					{
//						// White King has moved before
//						return false;
//					}
//					if (move.MovedPiece == 4)
//					{
//						// White Rook has moved before
//						return false;
//					}
//				}
//
//
//
//			}
//	}
//
//}
//
//
//return false;
//}