#pragma once
#include "../Movement/Movement.h"

class Board;
class PlayerTurn;
class PathTrace;
class MoveHistory;

enum class Team
{
	White = 1,
	Black = -1
};

class CheckMate
{
public:


	CheckMate();
	~CheckMate();

	bool isKingInCheckMate(const Board& board, const PlayerTurn& playerTurn, const PathTrace& pathrace, const  Team& _WhoseTeamTurn, const MoveHistory& history);


private:

	MoveData TempMoveData;


};