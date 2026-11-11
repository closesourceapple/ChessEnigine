#pragma once
#include "../Board/Board.h"
#include "../Movement/Movement.h"

class PathTrace
{
public:

	bool ClearPath_Horizontal(const Board& xboardx, const MoveData& xmovedatax)const;
	bool ClearPath_Vertical(const Board& xboardx, const MoveData& xmovedatax)const;
	bool ClearPath_Diagonal(const Board& xboardx, const MoveData& xmovedatax)const;

};