#pragma once


#include "../../Engine/Graphics/IndexBuffer/IndexBuffer.h"
#include "../../Engine/Graphics/VertexArray/VertexArray.h"
#include "../../Engine/Graphics/VertexBuffer/VertexBuffer.h"
#include "../../Engine/Graphics/VertexBufferLayout/VertexBufferLayout.h"
#include "../../Engine/Graphics/Renderer/Renderer.h"
#include "../../Engine/Graphics/Texture/Texture.h"
#include "../../Engine/Graphics/Shader/Shader.h"

#include <map>
#include "../../Engine/Vendor/glm/glm.hpp"

class Board;
class PlayerTurn;
enum class Team;

class ChessRenderer
{
private:
	enum class Texture_Key
	{
		BOARD = 0,
		NONE = 111 * 1111111,


		WHITE_PAWN = 1,
		WHITE_KNIGHT = 2,
		WHITE_BISHOP = 3,
		WHITE_ROOK = 4,
		WHITE_QUEEN = 5,
		WHITE_KING = 6,


		BLACK_PAWN = 7,
		BLACK_KNIGHT = 8,
		BLACK_BISHOP = 9,
		BLACK_ROOK = 10,
		BLACK_QUEEN = 11,
		BLACK_KING = 12,
	};


	static float vertices[16];
	static unsigned int indices[6];

	void DrawPawn();
	void setUV(Texture_Key piece_Type);
	void SetUVRect(float u0, float u1, float v0, float v1);
	Texture_Key	BoardPiece_to_TextureKey(int piece);
	void DrawPiece(Texture_Key piece, int boardX, int boardY);

	glm::vec2 BoardToScreen(int boardX, int boardY);

public:
	ChessRenderer();
	~ChessRenderer() = default;

	void DrawBoard(const Board& board, const PlayerTurn& playerTurn);
	void DrawChekMate_WhiteWins();
	void DrawCheckMate_BlackWins();



	void SetWindowSize_2i(unsigned int Height, unsigned int Width);

	float GetBoardX() const { return m_BoardX; }
	float GetBoardY() const { return m_BoardY; }
	float GetSquareSize() const { return m_SquareSize; }


private:

	int m_WindowHeight = 450, m_WindowWidth = 900;


	VertexArray VAO;
	VertexBuffer VBO;
	IndexBuffer IBO;
	VertexBufferLayout Layout;

	Shader m_Shader;
	Renderer m_Renderer;

	Texture m_BoardTexture;
	Texture m_PiecesTexture;
	Texture m_CheckMate_WhiteWins;
	Texture m_CheckMate_BlackWins;

	glm::mat4 m_Projection;
	glm::mat4 m_View;

	float m_BoardSize = 0.0f;
	float m_SquareSize = 0.0f;

	float m_BoardX = 0.0f;
	float m_BoardY = 0.0f;

};


