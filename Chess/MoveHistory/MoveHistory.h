#pragma once
#include "../Movement/Movement.h"
#include<vector>


struct MoveHistoryData
{
	MoveData HistoryData;
	int MovedPiece;
	int CapturedPiece;
};

class MoveHistory
{
public:
	void AddMove(MoveData HistoryData, int MovedPiece, int CapturedPiece);
	MoveHistoryData Get_LastMove() const;
	MoveHistoryData GetMove(int Index);


	int Size() const;
	bool Empty() const;
	void Clear();

private:
	std::vector<MoveHistoryData> m_History;
};