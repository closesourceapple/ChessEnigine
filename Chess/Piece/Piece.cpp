#include "_Piece.h"
#include "../Board/Board.h"
#include "../Movement/Movement.h"
#include "../PathTracing/PathTracing.h"


#include <cstdlib>

Piece::Piece() {}
Piece::~Piece() {}


Piece* Piece::PieceSelect(const Board& board, const MoveData& moveData)
{

	switch (abs(board.GetPiece(moveData.X_from, moveData.Y_from)))
	{
	case 1:
		return new Pawn;
		break;
	case 2:
		return new Knight;
		break;
	case 3:
		return new Bishop;
		break;
	case 4:
		return new Rook;
		break;
	case 5:
		return new Queen;
		break;
	case 6:
		return new King;
		break;
	default:
		return nullptr;
		break;
	}

}



// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //

