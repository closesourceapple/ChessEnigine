#pragma once

struct MoveData;


class Board {

private:
	mutable int board[8][8];

public:
	Board();
	~Board(); // destructor must be public so objects can be destroyed outside the class
	void Init_(); // initialize all pieces to the initial position
	void ApplyMoveValid_(bool PlayerTurn, bool PieceMove, const MoveData& GetData_);
	//void checkMove(bool bO0l);
	void ApplyMove_(const MoveData& GetData_);
	const int  GetPiece(const int x, const int y) const;
	void setPiece(int x, int y, int ReaplacementPiece) const;

};