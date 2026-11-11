#include "MoveHistory.h"

void MoveHistory::AddMove(MoveData HistoryData, int MovedPiece, int CapturedPiece)
{

	MoveHistoryData data;

	data.HistoryData = HistoryData;
	data.MovedPiece = MovedPiece;
	data.CapturedPiece = CapturedPiece;

	m_History.push_back(data);
}

MoveHistoryData MoveHistory::Get_LastMove() const
{
	if (!m_History.empty())
		return m_History.back();


	return MoveHistoryData{ 0,0,0 };
}

MoveHistoryData MoveHistory::GetMove(int Index)
{
	if (Index >= 0 && Index < m_History.size())
		return m_History[Index];


	return MoveHistoryData{ 0,0,0 };
}

int MoveHistory::Size() const
{
	return m_History.size();
}

bool MoveHistory::Empty() const
{
	return m_History.empty();
}

void ::MoveHistory::Clear()
{
	m_History.clear();
}