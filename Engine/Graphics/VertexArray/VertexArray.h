#pragma once

class VertexBuffer;   class VertexBufferLayout;


class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind();
	void Unbind();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& vb_layout);

private:
	unsigned int m_RendererID;
};