#include "ChessRenderer.h"

#include "../../Engine/Vendor/glm/glm.hpp"
#include "../../Engine/Vendor/glm/gtc/matrix_transform.hpp"

#include "../../Engine/Core/Window/Window.h"

#include "../../Chess/Board/Board.h"
#include "../../Chess/PlayerTurn/PlayerTurn.h"






enum class Team
{
	White = 1,
	Black = -1
};

unsigned int ChessRenderer::indices[6]
=
{
	0, 1, 2,
	2, 3, 0
};

float ChessRenderer::vertices[16] =
// Position      // Texture Coords
{
	//  0.0f,  0.0f,   0.0f, 0.0f,
	//512.0f,  0.0f,   1.0f, 0.0f,
	//512.0f,512.0f,   1.0f, 1.0f,
	// 0.0f, 512.0f,   0.0f, 1.0f

		// position      UV
		  0,   0,        0.0f,   0.0f,
		512,   0,        0.1667f,0.0f,
		512, 512,        0.1667f,0.5f,
		  0, 512,        0.0f,   0.5f

};



ChessRenderer::ChessRenderer()
	: VAO(),
	VBO(vertices, sizeof(vertices)),
	IBO(indices, 6),
	Layout(),
	m_Shader("../Assets/Shaders/basic.shader"),
	m_BoardTexture("../Assets/Textures/ChessBoard.png"),
	m_PiecesTexture("../Assets/Textures/ChessPieces.png"),
	m_CheckMate_WhiteWins("../Assets/Textures/WhiteWins.png"),
	m_CheckMate_BlackWins("../Assets/Textures/BlackWins.png"),
	m_Renderer(),
	m_Projection(1.0f),
	m_View(1.0f)
{

	Layout.push<float>(2);
	Layout.push<float>(2);

	VAO.AddBuffer(VBO, Layout);

	//m_Textures.emplace(Texture_Key::BOARD, Texture("Assets/Textures/ChessBoard.png"));
}

void ChessRenderer::DrawBoard(const Board& board, const PlayerTurn& playerTurn)
{


	m_Projection = glm::ortho(
		0.0f,
		(float)m_WindowWidth,
		0.0f,
		(float)m_WindowHeight,
		-1.0f,
		1.0f
	);

	// Board ...
	glm::mat4 Model_Matrix(1.0f);
	m_BoardSize = std::min(m_WindowWidth, m_WindowHeight) * 0.9f;
	m_SquareSize = m_BoardSize / 8.0f;

	m_BoardX = (m_WindowWidth - m_BoardSize) / 2.0f;
	m_BoardY = (m_WindowHeight - m_BoardSize) / 2.0f;

	Model_Matrix = glm::translate(
		Model_Matrix,
		glm::vec3(
			m_BoardX,
			m_BoardY,
			0.0f
		)
	);
	m_SquareSize = m_BoardSize / 8.0f;
	Model_Matrix = glm::scale(
		Model_Matrix,
		glm::vec3(
			m_BoardSize / 512.0f,
			m_BoardSize / 512.0f,
			1.0f
		)
	);


	glm::mat4 BoardMVP = m_Projection * m_View * Model_Matrix;


	setUV(Texture_Key::BOARD);
	m_Shader.Bind();
	VAO.Bind();
	IBO.Bind();

	m_BoardTexture.Bind();
	m_Shader.SetUniform1i("u_Texture", 0);
	m_Shader.SetUniformMat4f("u_MVP", BoardMVP);

	m_Renderer.Draw(VAO, IBO, m_Shader);
	m_BoardTexture.Unbind();


	// Pieces ...
	m_PiecesTexture.Bind();
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			int piece = board.GetPiece(x, y);

			if (piece == 0)
				continue;

			//if (playerTurn.GetTurn() == true)// white turn it is a bug but because of it board looks cool it is fine 
			// i will add an way of playing thing if needed but for now enjoy :]

			DrawPiece(BoardPiece_to_TextureKey(piece), x, y);
			//else
			//{
			//	DrawPiece(BoardPiece_to_TextureKey(piece), x, y);
			//}
		}
	}

	m_PiecesTexture.Unbind();

}
void ChessRenderer::DrawChekMate_WhiteWins()
{

	float popupWidth = m_WindowWidth * 0.50f;
	float popupHeight = m_WindowHeight * 0.35f;

	float popupX =
		(m_WindowWidth - popupWidth) / 2.0f;

	float popupY =
		(m_WindowHeight - popupHeight) / 2.0f;


	glm::mat4 Model_Matrix(1.0f);

	Model_Matrix = glm::translate(
		Model_Matrix,
		glm::vec3(
			popupX,
			popupY,
			0.0f
		)
	);

	Model_Matrix = glm::scale(
		Model_Matrix,
		glm::vec3(
			popupWidth / 512.0f,
			popupHeight / 512.0f,
			1.0f
		)
	);


	glm::mat4 MVP =
		m_Projection *
		m_View *
		Model_Matrix
		;


	setUV(Texture_Key::BOARD);

	m_Shader.Bind();
	VAO.Bind();
	IBO.Bind();

	m_CheckMate_WhiteWins.Bind();

	m_Shader.SetUniform1i(
		"u_Texture",
		0
	);

	m_Shader.SetUniformMat4f(
		"u_MVP",
		MVP
	);

	m_Renderer.Draw(
		VAO,
		IBO,
		m_Shader
	);

	m_CheckMate_WhiteWins.Unbind();



}
void ChessRenderer::DrawCheckMate_BlackWins()
{

	float popupWidth = m_WindowWidth * 0.50f;
	float popupHeight = m_WindowHeight * 0.35f;

	float popupX =
		(m_WindowWidth - popupWidth) / 2.0f;

	float popupY =
		(m_WindowHeight - popupHeight) / 2.0f;


	glm::mat4 Model_Matrix(1.0f);

	Model_Matrix = glm::translate(
		Model_Matrix,
		glm::vec3(
			popupX,
			popupY,
			0.0f
		)
	);

	Model_Matrix = glm::scale(
		Model_Matrix,
		glm::vec3(
			popupWidth / 512.0f,
			popupHeight / 512.0f,
			1.0f
		)
	);


	glm::mat4 MVP =
		m_Projection *
		m_View *
		Model_Matrix
		;


	setUV(Texture_Key::BOARD);

	m_Shader.Bind();
	VAO.Bind();
	IBO.Bind();

	m_CheckMate_BlackWins.Bind();

	m_Shader.SetUniform1i(
		"u_Texture",
		0
	);

	m_Shader.SetUniformMat4f(
		"u_MVP",
		MVP
	);

	m_Renderer.Draw(
		VAO,
		IBO,
		m_Shader
	);

	m_CheckMate_BlackWins.Unbind();



}
void ChessRenderer::SetWindowSize_2i(unsigned int Height, unsigned int Width)
{
	m_WindowHeight = Height;
	m_WindowWidth = Width;

	m_Projection = glm::ortho(
		0.0f,
		(float)m_WindowWidth,
		0.0f,
		(float)m_WindowHeight,
		-1.0f,
		1.0f
	);

}

// fill all of the pieces 
void ChessRenderer::setUV(Texture_Key piece_Type)
{

	switch (piece_Type)
	{
	case ChessRenderer::Texture_Key::BOARD:
		//SetUVRect(0.0f, 1.0f, 0.0f, 1.0f);
		SetUVRect(0.0f, 1.0f, 0.0f, 1.0f);
		break;

	case ChessRenderer::Texture_Key::WHITE_PAWN:
		SetUVRect(0.8333f, 1.0000f, 0.5f, 1.0f); // White Pawn
		break;

	case ChessRenderer::Texture_Key::WHITE_KNIGHT:
		SetUVRect(0.5000f, 0.6667f, 0.5f, 1.0f); // White Knight
		break;

	case ChessRenderer::Texture_Key::WHITE_BISHOP:
		SetUVRect(0.3333f, 0.5000f, 0.5f, 1.0f); // White Bishop
		break;

	case ChessRenderer::Texture_Key::WHITE_ROOK:
		SetUVRect(0.6667f, 0.8333f, 0.5f, 1.0f); // White Rook
		break;

	case ChessRenderer::Texture_Key::WHITE_QUEEN:
		SetUVRect(0.1667f, 0.3333f, 0.5f, 1.0f); // White Queen
		break;

	case ChessRenderer::Texture_Key::WHITE_KING:
		SetUVRect(0.0000f, 0.1667f, 0.5f, 1.0f); // White King

		break;
	case ChessRenderer::Texture_Key::BLACK_PAWN:
		SetUVRect(0.8333f, 1.0000f, 0.0f, 0.5f); // Black Pawn
		break;

	case ChessRenderer::Texture_Key::BLACK_KNIGHT:
		SetUVRect(0.5000f, 0.6667f, 0.0f, 0.5f); // Black Knight
		break;

	case ChessRenderer::Texture_Key::BLACK_BISHOP:
		SetUVRect(0.3333f, 0.5000f, 0.0f, 0.5f); // Black Bishop
		break;

	case ChessRenderer::Texture_Key::BLACK_ROOK:
		SetUVRect(0.6667f, 0.8333f, 0.0f, 0.5f); // Black Rook
		break;

	case ChessRenderer::Texture_Key::BLACK_QUEEN:
		SetUVRect(0.1667f, 0.3333f, 0.0f, 0.5f); // Black Queen
		break;

	case ChessRenderer::Texture_Key::BLACK_KING:
		SetUVRect(0.0000f, 0.1667f, 0.0f, 0.5f); // Black King
		break;


	default:
		break;
	}

	VBO.Update(vertices, sizeof(vertices));
}

void ChessRenderer::SetUVRect(float u0, float u1, float v0, float v1)
{
	vertices[2] = u0;
	vertices[3] = v0;

	vertices[6] = u1;
	vertices[7] = v0;

	vertices[10] = u1;
	vertices[11] = v1;

	vertices[14] = u0;
	vertices[15] = v1;
}







glm::vec2 ChessRenderer::BoardToScreen(int boardX, int boardY)
{
	return glm::vec2(
		m_BoardX + boardX * m_SquareSize,
		m_BoardY + (7 - boardY) * m_SquareSize
	);
}



void ChessRenderer::DrawPiece(Texture_Key piece, int boardX, int boardY)
{
	setUV(piece);
	glm::vec2 pos = BoardToScreen(boardX, boardY);

	glm::mat4 Model(1.0f);

	Model = glm::translate(
		Model,
		glm::vec3(pos.x, pos.y, 0.0f)
	);

	Model = glm::scale(
		Model,
		glm::vec3(
			m_SquareSize / 512.0f,
			m_SquareSize / 512.0f,
			1.0f
		)
	);

	glm::mat4 view(1.0f);

	glm::mat4 projection = glm::ortho(
		0.0f,
		(float)m_WindowWidth,
		0.0f,
		(float)m_WindowHeight,
		-1.0f,
		1.0f
	);

	glm::mat4 MVP = projection * view * Model;

	//m_PiecesTexture.Bind();
	m_Shader.SetUniformMat4f("u_MVP", MVP);

	m_Renderer.Draw(VAO, IBO, m_Shader);

}

ChessRenderer::Texture_Key ChessRenderer::BoardPiece_to_TextureKey(int piece)
{
	switch (piece)
	{
		// White Pieces
	case  1: return Texture_Key::WHITE_PAWN;
	case  2: return Texture_Key::WHITE_KNIGHT;
	case  3: return Texture_Key::WHITE_BISHOP;
	case  4: return Texture_Key::WHITE_ROOK;
	case  5: return Texture_Key::WHITE_QUEEN;
	case  6: return Texture_Key::WHITE_KING;

		// Black Pieces
	case -1: return Texture_Key::BLACK_PAWN;
	case -2: return Texture_Key::BLACK_KNIGHT;
	case -3: return Texture_Key::BLACK_BISHOP;
	case -4: return Texture_Key::BLACK_ROOK;
	case -5: return Texture_Key::BLACK_QUEEN;
	case -6: return Texture_Key::BLACK_KING;

	default:
		return Texture_Key::NONE; // or another NONE/INVALID value if you add one
	}


	return Texture_Key::NONE;;
}





//DrawPiece(Texture_Key piece, int boardX, int boardY)
//│
//├── setUV(piece)
//├── BoardToScreen(boardX, boardY)
//├── Create Model Matrix
//├── Translate
//├── Scale
//├── Build MVP
//├── Bind shader
//├── Bind texture
//└── Draw




// Pieces .".
//		OLD PAWN ONLY NOT FOR IMPLIMENTATION
// 
// 
//void ChessRenderer::DrawPawn()
//{
//	glm::mat4 Model_Matrix(1.0f);
//	int BoardSize = std::min(m_WindowWidth, m_WindowHeight) * 0.9f;
//
//	Model_Matrix = glm::translate(
//		Model_Matrix,
//		glm::vec3(
//			(m_WindowWidth - BoardSize) / 2.0f,
//			(m_WindowHeight - BoardSize) / 2.0f,
//			0.0f
//		)
//	);
//
//
//
//	Model_Matrix = glm::scale(
//		Model_Matrix,
//		glm::vec3(
//			BoardSize / 512.0f,
//			BoardSize / 512.0f,
//			1.0f
//		)
//	);	glm::mat4 view = glm::mat4(1.0f);
//
//	glm::mat4 projection =
//		glm::ortho(
//			0.0f,				  // Left
//			(float)m_WindowWidth, // Right
//			0.0f,				  // Bottom
//			(float)m_WindowHeight,// Top
//			-1.0f,				  // Near
//			1.0f              	  // Far
//		);
//
//	glm::mat4 MVP = projection * view * Model_Matrix;
//
//
//
//}
