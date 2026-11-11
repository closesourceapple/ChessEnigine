#include "Check.h"
#include "..\Board\Board.h"
#include "..\PlayerTurn\PlayerTurn.h"
#include "..\Movement\Movement.h"
#include "..\Piece\_Piece.h"
#include "..\PathTracing\PathTracing.h"
#include "../CheckMate/CheckMate.h"
#include "../MoveHistory/MoveHistory.h"

#include<iostream>



void Check::findKing(const Board& board)
{

	for (int i = 0; i < 8; i++) //x axis
	{
		for (int j = 0; j < 8; j++)//y axis
		{
			piece = board.GetPiece(i, j);
			if (piece == 6)
			{
				kingX_white = i; kingY_white = j;
			}
			if (piece == -6)
			{
				kingX_black = i; kingY_black = j;
			}
		}
	}


}

void Check::setPlayerTurn(const PlayerTurn& playerturn)
{
	isWhiteTurn = playerturn.GetTurn();
}

bool Check::WhiteKingInCheck_(const Board& board, const MoveHistory& history)
{


	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++) {

			if (board.GetPiece(i, j) < 0)
			{

				TempMoveData.X_from = i;
				TempMoveData.Y_from = j;
				TempMoveData.X_to = kingX_white;
				TempMoveData.Y_to = kingY_white;

				Piece* piecep = Piece::PieceSelect(board, TempMoveData);
				PathTrace pathtrace;

				if (piecep == nullptr)
				{
					continue;
				}


				if (piecep->Controller(board, TempMoveData, pathtrace, history))
				{
					delete piecep;
					return true;
				}


				delete piecep;
			}
		}

	}
	return false;
}

bool Check::BlackKingInCheck_(const Board& board, const MoveHistory& historya)
{

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++) {

			if (board.GetPiece(i, j) > 0)
			{

				TempMoveData.X_from = i;
				TempMoveData.Y_from = j;
				TempMoveData.X_to = kingX_black;
				TempMoveData.Y_to = kingY_black;

				Piece* piece = Piece::PieceSelect(board, TempMoveData);
				PathTrace pathtrace;



				if (piece == nullptr)
				{
					continue;
				}

				if (piece->Controller(board, TempMoveData, pathtrace, historya))
				{
					delete piece;
					return true;
				}


				delete piece;
			}
		}

	}

	return false;
}

bool Check::MoveKeepsKingSafe(const Board& board,
	const MoveData& moveData, const Team& _WhichTeam, const MoveHistory& historya)
{
	Board tempBoard = board;

	tempBoard.ApplyMove_(moveData);

	;
	findKing(tempBoard);

	if (_WhichTeam == Team::White)
	{
		bool inCheck = this->WhiteKingInCheck_(tempBoard, historya);
		return !inCheck;
	}

	if (_WhichTeam == Team::Black)
	{
		bool inCheck = this->BlackKingInCheck_(tempBoard, historya);
		return !inCheck;
	}


	return false;
	//return !check.(tempBoard);
}
