#pragma once

class Check;
class Board;
class MoveHistory;
struct MoveData;
class PathTrace;

class SpecialMoves {
public:
	static bool PromotionCheck(Board& board, const MoveData& moveData, int MovedPiece);

	static bool CastlingCheck(const Board& board, const MoveData& moveData, MoveHistory& history, PathTrace& trace, Check& check);

	static void ApplyCastling(Board& board, const MoveData& moveData);

};