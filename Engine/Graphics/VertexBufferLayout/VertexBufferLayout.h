#pragma once

#include <vector>


struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

};


class VertexBufferLayout
{
public:
	VertexBufferLayout();
	~VertexBufferLayout() = default;

	template <class T>
	void push(unsigned int)
	{
		static_assert(sizeof(T) == 0, "Unsupported Type");
	}



	const std::vector<VertexBufferElement>& GetElements() const;
	unsigned int GetStride() const;

	static int GetSizeOfType(unsigned int Type);

private:
	unsigned int m_Stride;
	std::vector<VertexBufferElement> m_Elements;
};

template<>
void VertexBufferLayout::push<float>(unsigned int);

template<>
void VertexBufferLayout::push<unsigned int>(unsigned int);

template<>
void VertexBufferLayout::push<unsigned char>(unsigned int);