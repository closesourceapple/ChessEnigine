#pragma once
#include "../Movement/Movement.h"
#include "../CheckMate/CheckMate.h"


class Board;
class PlayerTurn;
class CheckMate;
enum class Team;









class Check
{
public:
	void findKing(const Board& board);
	void setPlayerTurn(const PlayerTurn& playerturn);
	bool WhiteKingInCheck_(const Board& board, const MoveHistory& history);
	bool BlackKingInCheck_(const Board& board, const MoveHistory& historya);
	bool MoveKeepsKingSafe(const Board& board, const MoveData& moveData, const Team& _WhichTeam, const MoveHistory& historya);

private:
	int kingX_white, kingY_white;
	int kingX_black, kingY_black;
	int piece;
	bool isWhiteTurn;
	MoveData TempMoveData;
};

