#pragma once

class Board;
struct MoveData;
struct PathTrace;
class MoveHistory;

class Piece
{
public:

	Piece();
	virtual ~Piece() = 0;
	static Piece* PieceSelect(const Board& board, const MoveData& moveData);

	virtual bool Controller(const Board& xboardx, const MoveData& xmovedatax, const PathTrace&, const MoveHistory& history) = 0;

private:
};




class Pawn : public Piece
{
public:

	bool Controller(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace, const MoveHistory& history);

	bool MoveValidVertical(const Board& xboardx, const MoveData& xmovedatax);
	bool FirstMove(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace);
	bool DiagonalPieceCaputure(const Board& xboardx, const MoveData& xmovedatax);
	bool ENpasant(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace, const MoveHistory& HisTory);

};



class Knight : public Piece
{
public:
	bool Controller(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace, const MoveHistory& history);
	bool  MoveValid_vertical(const Board& xboardx, const MoveData& xmovedatax);

};

class  Bishop : public Pawn
{
public:

	bool Controller(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace, const MoveHistory& history);
	bool  MoveValid_diagonal(const Board& xboardx, const MoveData& xmovedatax);


};

class Rook : public Piece
{
public:
	bool Controller(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace, const MoveHistory& history);
	bool MoveValid_vertical(const Board& xboardx, const MoveData& xmovedatax);
	bool ClearPath(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace);

};

class Queen : public Piece
{
public:
	bool Controller(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace, const MoveHistory& history);

	bool MoveValid_vertical(const Board& xboardx, const MoveData& xmovedatax);
	bool MoveValid_horizontal(const Board& xboardx, const MoveData& xmovedatax);
	bool MoveValid_diagonal(const Board& xboardx, const MoveData& xmovedatax);

	bool ClearPath_vertical(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace);
	bool ClearPath_horizontal(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace);
	bool ClearPath_diagonal(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace);

};

class King : public Piece
{
public:
	bool Controller(const Board& xboardx, const MoveData& xmovedatax, const PathTrace& pathTrace, const MoveHistory& history);
	bool  MoveValid_(const Board& xboardx, const MoveData& xmovedatax);

};