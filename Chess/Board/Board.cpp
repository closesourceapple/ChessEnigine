#include "Board.h";
#include "../Movement/Movement.h"

Board::Board()
{

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j] = 0;

		}
	}
}
Board::~Board() {}


void Board::Init_()
{
	// a8 is 00 , a7 is 01



	// black pieces

	// black pawn 
	for (int i = 0; i < 8; i++)
	{
		board[i][1] = -1;
	}
	// rooks 
	board[0][0] = -4;
	board[7][0] = -4;
	// knight
	board[1][0] = -2;
	board[6][0] = -2;
	// bishop
	board[2][0] = -3;
	board[5][0] = -3;
	//queen
	board[3][0] = -5;
	//king 
	board[4][0] = -6;



	// white pieces 

	//white pawn
	for (int i = 0; i < 8; i++)
	{
		board[i][6] = 1;
	}
	// rooks
	board[0][7] = 4;
	board[7][7] = 4;
	// knight
	board[1][7] = 2;
	board[6][7] = 2;
	// bishop
	board[2][7] = 3;
	board[5][7] = 3;
	//queen
	board[3][7] = 5;
	//king 
	board[4][7] = 6;


}



void Board::ApplyMoveValid_(bool PlayerTurn, bool PieceMove, const MoveData& GetData_)
{
	if (PlayerTurn && PieceMove)
	{
		this->ApplyMove_(GetData_);
	}



}





void Board::ApplyMove_(const MoveData& GetData_)
{
	board[GetData_.X_to][GetData_.Y_to] =
		board[GetData_.X_from][GetData_.Y_from];

	board[GetData_.X_from][GetData_.Y_from] = 0;
}

const int  Board::GetPiece(const int x, const int y) const
{
	return board[x][y];
}

void Board::setPiece(int x, int y, int ReaplacementPiece) const
{
	board[x][y] = ReaplacementPiece;
}

