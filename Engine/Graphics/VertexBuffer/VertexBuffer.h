#pragma once

class VertexBuffer
{
public:
	VertexBuffer(const void* data, const unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void Update(const void* data, unsigned int size) const;

private:

	unsigned int m_RendererID;
};