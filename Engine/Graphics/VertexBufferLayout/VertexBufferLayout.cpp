#include "VertexBufferLayout.h"

#include <GL/glew.h>
#include "../Renderer/Renderer.h"






VertexBufferLayout::VertexBufferLayout() :m_Stride(0) {}

const std::vector<VertexBufferElement>& VertexBufferLayout::GetElements() const
{
	// TODO: insert return statement here
	return m_Elements;
}

unsigned int VertexBufferLayout::GetStride() const
{
	return m_Stride;
}

int VertexBufferLayout::GetSizeOfType(unsigned int Type)
{
	switch (Type)
	{

	case GL_FLOAT:		    return sizeof(float);
	case GL_UNSIGNED_INT:	return sizeof(unsigned int);
	case GL_UNSIGNED_BYTE:	return sizeof(unsigned char);
	}
	ASSERT(false);
	return 0;
}

template<>
void VertexBufferLayout::push<float>(unsigned int count)
{
	m_Elements.push_back({ GL_FLOAT , (unsigned int)count , false });
	m_Stride += GetSizeOfType(GL_FLOAT) * count;
}
template<>
void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
	m_Elements.push_back({ GL_UNSIGNED_INT , (unsigned int)count , false });
	m_Stride += GetSizeOfType(GL_UNSIGNED_INT) * count;

}
template<>
void VertexBufferLayout::push<unsigned char>(unsigned int count)
{
	m_Elements.push_back({ GL_UNSIGNED_BYTE , (unsigned int)count , false });
	m_Stride += GetSizeOfType(GL_UNSIGNED_BYTE) * count;
}

