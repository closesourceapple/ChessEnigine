#include "PathTracing.h"
#include <cstdlib>


bool PathTrace::ClearPath_Horizontal(const Board& xboardx, const MoveData& xmovedatax)const
{
	if (xmovedatax.Y_from != xmovedatax.Y_to)
	{
		return false;
	}
	if (xmovedatax.X_from < xmovedatax.X_to)
	{
		for (int i = abs(xmovedatax.X_from + 1); i < abs(xmovedatax.X_to); i++)
		{

			if (xboardx.GetPiece(i, xmovedatax.Y_from) != 0)
			{
				return true;
				break;
			}
		}
	}
	if (xmovedatax.X_from > xmovedatax.X_to)
	{
		for (int i = abs(xmovedatax.X_from - 1); i > abs(xmovedatax.X_to); i--)
		{

			if (xboardx.GetPiece(i, xmovedatax.Y_from) != 0)
			{
				return true;
				break;
			}
		}
	}
	return false;
}


bool PathTrace::ClearPath_Vertical(const Board& xboardx, const MoveData& xmovedatax)const
{
	if (xmovedatax.X_from != xmovedatax.X_to)
	{
		return false;
	}
	if (xmovedatax.Y_from < xmovedatax.Y_to)
	{
		for (int i = abs(xmovedatax.Y_from + 1); i < abs(xmovedatax.Y_to); i++)
		{
			if (xboardx.GetPiece(xmovedatax.X_from, i) != 0)
			{
				return true;
				break;
			}
		}
	}
	if (xmovedatax.Y_from > xmovedatax.Y_to)
	{
		for (int i = abs(xmovedatax.Y_from - 1); i > abs(xmovedatax.Y_to); i--)
		{

			if (xboardx.GetPiece(xmovedatax.X_from, i) != 0)
			{
				return true;
				break;
			}
		}
	}
	return false;
}

bool ::PathTrace::ClearPath_Diagonal(const Board& xboardx, const MoveData& xmovedatax)const
{
	if (xmovedatax.X_from < xmovedatax.X_to && xmovedatax.Y_from < xmovedatax.Y_to)
	{
		for (int Xstep = xmovedatax.X_from + 1, Ystep = xmovedatax.Y_from + 1;(Xstep < xmovedatax.X_to) && (Ystep < xmovedatax.Y_to); Xstep++, Ystep++)
		{

			if (xboardx.GetPiece(Xstep, Ystep))
			{
				return true;
				break;
			}
		}
	}


	if (xmovedatax.X_to < xmovedatax.X_from && xmovedatax.Y_to < xmovedatax.Y_from)
	{
		for (int Xstep = abs(xmovedatax.X_from) - 1, Ystep = abs(xmovedatax.Y_from) - 1;(Xstep > xmovedatax.X_to) && (Ystep > xmovedatax.Y_to); Xstep--, Ystep--)
		{


			if (xboardx.GetPiece(Xstep, Ystep))
			{
				return true;
				break;
			}
		}
	}


	if (xmovedatax.X_to > xmovedatax.X_from && xmovedatax.Y_to < xmovedatax.Y_from)
	{
		for (int Xstep = xmovedatax.X_from + 1, Ystep = xmovedatax.Y_from - 1;(Xstep < xmovedatax.X_to) && (Ystep > xmovedatax.Y_to); Xstep++, Ystep--)
		{

			if (xboardx.GetPiece(Xstep, Ystep))
			{
				return true;
				break;
			}
		}
	}


	if (xmovedatax.X_to < xmovedatax.X_from && xmovedatax.Y_to > xmovedatax.Y_from)
	{
		for (int Xstep = xmovedatax.X_from - 1, Ystep = xmovedatax.Y_from + 1;(Xstep > xmovedatax.X_to) && (Ystep < xmovedatax.Y_to); Xstep--, Ystep++)
		{

			if (xboardx.GetPiece(Xstep, Ystep))
			{
				return true;
				break;
			}
		}
	}

	return false;
}