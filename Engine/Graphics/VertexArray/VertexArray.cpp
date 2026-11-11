#include "VertexArray.h"

#include <GL/glew.h>
#include "../VertexBuffer/VertexBuffer.h"
#include "../VertexBufferLayout/VertexBufferLayout.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind()
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& vb_layout)
{
	Bind();
	vb.Bind();

	const auto& elements = vb_layout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, vb_layout.GetStride(), (const void*)(uintptr_t)offset);

		offset += element.count * VertexBufferLayout::GetSizeOfType(element.type);

	}


}