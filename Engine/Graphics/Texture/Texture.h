#pragma once

#include <string>

class Texture
{
public:
	Texture(const std::string& FilePath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	int GetHeight() const;
	int GetWidth()  const;

private:
	unsigned int m_RendererID;
	std::string m_FilePath;

	unsigned char* m_LocalBuffer;

	int m_Width, m_Height;
	int m_BPP;
};

//Texture
//│
//├── Constructor
//├── Destructor
//├── Bind(unsigned int slot = 0)
//├── UnBind()
//│
//├── GetWidth()
//├── GetHeight()
//│
//├── m_RendererID
//├── m_FilePath
//├── m_LocalBuffer
//├── m_Width
//├── m_Height
//└── m_BPP - (Bytes Per Pixel)