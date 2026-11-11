#pragma once



// external classes
class VertexArray; class IndexBuffer; class Shader;

class Renderer
{
public:
	Renderer() {}
	~Renderer() {}

	void Draw(VertexArray& va, const IndexBuffer& ib, const Shader& shader);
private:

};




// the safety thing <3
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLcall(x) GLclearError();\
x;\
	ASSERT(GlLogCall(#x,__FILE__, __LINE__))

void GLclearError();
bool GlLogCall(const char* function, const char* file, int line);