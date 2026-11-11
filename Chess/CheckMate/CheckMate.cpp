#include "CheckMate.h"
#include "../Board/Board.h"
#include "../Piece/_Piece.h"
#include "../Check/Check.h"
#include "../PlayerTurn/PlayerTurn.h"
#include "../PathTracing/PathTracing.h"


CheckMate::CheckMate()

{
}

CheckMate::~CheckMate()
{
}

bool CheckMate::isKingInCheckMate(const Board& board, const PlayerTurn& playerTurn, const PathTrace& pathrace, const  Team& _WhoseTeamTurn, const MoveHistory& history)
{

	Check CheckMateWhite;

	Check checker;


	int sign = (_WhoseTeamTurn == Team::White) ? 1 : -1;

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (board.GetPiece(x, y) * sign <= 0)
				continue;

			TempMoveData.X_from = x;
			TempMoveData.Y_from = y;

			for (int toX = 0; toX < 8; toX++)
			{
				for (int toY = 0; toY < 8; toY++)
				{
					TempMoveData.X_to = toX;
					TempMoveData.Y_to = toY;

					Piece* currentPiece = Piece::PieceSelect(board, TempMoveData);

					if (!currentPiece)
						continue;

					if (currentPiece->Controller(board, TempMoveData, pathrace, history) &&
						checker.MoveKeepsKingSafe(board, TempMoveData, _WhoseTeamTurn, history))
					{
						delete currentPiece;
						return false; // Not checkmate, found an escape move
					}

					delete currentPiece;
				}
			}
		}
	}

	return true; // No legal move exists
}

