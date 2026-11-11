#include "Renderer.h"

#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include <iostream>

#include "../IndexBuffer/IndexBuffer.h"
#include "../VertexArray/VertexArray.h"
#include "../Shader/Shader.h"

void GLclearError()
{
	while (glGetError() != GL_NO_ERROR)
	{

	}
}

bool GlLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "GL ERROR : (\n" << error << ") : " << file << " : " << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Draw(VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	shader.Bind();
	va.Bind();
	ib.Bind();


	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);

}



































// first verison of renderer  :> 
//
//const char Renderer::setPieceToChar(const int _PieceInt) const
//{
//	switch (_PieceInt)
//	{
//	case -1:
//		return 'p';
//		break;
//	case -2:
//		return 'n';
//		break;
//	case -3:
//		return 'b';
//		break;
//	case -4:
//		return 'r';
//		break;
//	case -5:
//		return 'q';
//		break;
//	case -6:
//		return 'k';
//		break;
//
//
//
//	case 1:
//		return 'P';
//		break;
//	case 2:
//		return 'N';
//		break;
//	case 3:
//		return 'B';
//		break;
//	case 4:
//		return 'R';
//		break;
//	case 5:
//		return 'Q';
//		break;
//	case 6:
//		return 'K';
//		break;
//
//
//
//	default:
//
//		return '.';
//		break;
//	}
//}
//void Renderer::PrintBoard(const Board& PieceBoard_) const
//{
//	std::cout << "      ------------------------------------\n";
//	std::cout << "      |   a   b   c   d   e   f   g   h  |\n";
//	std::cout << "      ------------------------------------\n";
//
//	std::cout << "\n";
//	std::cout << "-     -------------------------------------";
//	std::cout << "\n";
//
//	for (int x = 0; x < 8; x++)
//	{
//		std::cout << 8 - (x) << "|    |   ";
//		for (int y = 0; y < 8; y++)
//		{
//			std::cout << setPieceToChar(PieceBoard_.GetPiece(y, x)) << "   ";
//
//		}
//		std::cout << "|\n |    |                                   |\n";
//	}
//	std::cout << "-     -------------------------------------\n\n";
//
//	std::cout << glfwInit();
//
//}
//
//void Renderer::PrintMessage(const char* message)
//{
//
//	std::cout << message;
//
//}

