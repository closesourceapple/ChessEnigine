#include "..\Chess\Board/Board.h"
#include "..\Chess\Movement/Movement.h"
#include "..\Chess\PlayerTurn/PlayerTurn.h"
#include "..\Chess\Piece/_Piece.h"
#include "..\Chess\PathTracing/PathTracing.h"
#include "..\Chess\Check/Check.h"
#include "..\Chess\CHeckMate/CheckMate.h"
#include "../Chess/MoveHistory/MoveHistory.h"
#include "../Chess/Piece/SpecialMoves/SpecialMoves.h"

#include "../Engine/Core/Window/Window.h"
#include "../Engine/Graphics/Blend/Blend.h"
#include"../Engine/MusicManager/AudioSource/AudioManager/MusicManger.h"

#include "ChessInput/ChessInput.h"
#include "ChessRenderer/ChessRenderer.h"
#include "ChessAudio/ChessAudio.h"

#include <Windows.h>
#include <iostream>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	bool isRunning = true;
	bool isRestart = false;
	while (isRunning)
	{
		isRestart = false;

		MusicManger::Init();
		Board board;
		MoveData moveData;

		PlayerTurn playerTurn;
		PathTrace pathTrace;
		Check check;
		CheckMate checkMate;
		MoveHistory History;

		Window CurrentWindow(850, 1200, "CHESS");
		//Window LWindow(33, 55, "alu");
		ChessRenderer render;
		ChessInput input(&CurrentWindow, &render);
		ChessAudio audio;

		Piece* piece = nullptr;

		board.Init_();

		Blend::Enable();




		int isCheckMate = false;// 0 - no checkmate,1 white wins ,-1 black wins





		while (!CurrentWindow.ShouldClose() && !isRestart && isRunning)
		{

			CurrentWindow.BeginFrame();

			render.SetWindowSize_2i(
				CurrentWindow.GetHeight(),
				CurrentWindow.GetWidth()
			);

			input.Update();



			if (isCheckMate != 0)
			{
				input.UpdateWinScreenButtons(isCheckMate);
				int8_t	action = input.LastMoves();

				if (action == 1)
				{
					isRestart = true;
				}
				if (action == 2)
				{
					isRunning = false;
					CurrentWindow.Close();

				}
			}

			if (input.NewMove() && isCheckMate == 0)
			{
				moveData = input.GetMoveData();

				piece = Piece::PieceSelect(board, moveData);

				if (piece != nullptr)
				{
					bool turnOk =
						playerTurn.IscurrectTurn(board, moveData);

					bool castle = false;
					bool moveOk = false;
					bool safeOk = false;

					if (turnOk)
					{
						// First check special move
						castle = SpecialMoves::CastlingCheck(
							board,
							moveData,
							History,
							pathTrace,
							check
						);

						if (castle)
						{

							SpecialMoves::ApplyCastling(board, moveData);

							moveOk = true;
							safeOk = true;
						}
						else
						{
							// Normal move
							moveOk =
								piece->Controller(
									board,
									moveData,
									pathTrace,
									History
								);

							if (moveOk)
							{
								Team currentTeam =
									playerTurn.GetTurn()
									? Team::White
									: Team::Black;

								safeOk =
									check.MoveKeepsKingSafe(
										board,
										moveData,
										currentTeam,
										History
									);
							}
						}

						// IMPORTANT:
						// This is OUTSIDE the castle/non-castle branches.
						if (turnOk && moveOk && safeOk)
						{

							int movedPiece =
								board.GetPiece(
									moveData.X_from,
									moveData.Y_from
								);

							int capturedPiece =
								board.GetPiece(
									moveData.X_to,
									moveData.Y_to
								);

							audio.PlayPieceMoved();




							if (castle)
							{
								board.ApplyMove_(moveData);

								SpecialMoves::ApplyCastling(
									board,
									moveData
								);
							}
							else
							{
								board.ApplyMove_(moveData);
							}

							if (checkMate.isKingInCheckMate(board, playerTurn, pathTrace, Team::Black, History))
								isCheckMate = 1;

							if (checkMate.isKingInCheckMate(board, playerTurn, pathTrace, Team::White, History))
								isCheckMate = -1;



							SpecialMoves::PromotionCheck(
								board,
								moveData,
								movedPiece
							);

							History.AddMove(
								moveData,
								movedPiece,
								capturedPiece
							);

							playerTurn.ifMoveSuceed_changeTurn();

						}
					}
				}

				delete piece;
				piece = nullptr;
			}



			render.DrawBoard(board, playerTurn);

			if (isCheckMate == 1)
				render.DrawChekMate_WhiteWins();
			if (isCheckMate == -1)
				render.DrawCheckMate_BlackWins();



			CurrentWindow.EndFrame();



		}
		if (CurrentWindow.ShouldClose())
			isRunning = false;
		MusicManger::ShutDown();

	}

	return 0;
}

