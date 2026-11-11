#include "Shader.h"

#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <stdexcept>




// Constructer and Destrucor
Shader::Shader(const std::string& filePath)
	:m_FilePath(filePath), m_RendererID(0), source({})
{
	source = ParseShader(filePath);
	m_RendererID = CreateShader(source.VertexShader, source.FragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}


// Bind and UnBind
void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}


void Shader::SetUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

//void Shader::SetUniformMat4f(const std::string& name, const glm::mat4 matrix)
//{
//	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
//}

void Shader::SetUniform1f(const std::string& name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}


/////////////// nothing to do with Rather than debugging ////////////////


// Private Functions 

//
int Shader::GetUniformLocation(const std::string& name)
{
	// Priviously Located.
	if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
		return m_uniformLocationCache[name];

	// Newly Created.
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());

	if (location == -1)
	{
		std::string error = name + " Does't exist!\n";
		throw std::runtime_error(error);
	}

	m_uniformLocationCache[name] = location;

	return location;
}

ShaderProgramSource Shader::ParseShader(const std::string& FilePath)
{
	std::ifstream stream(FilePath);
	std::stringstream ss[2];
	std::string line;

	enum class  ShaderType {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};
	ShaderType TYPE = ShaderType::NONE;

	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				TYPE = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				TYPE = ShaderType::FRAGMENT;
			}
		}
		else if (TYPE != ShaderType::NONE)
		{
			ss[static_cast<int>(TYPE)] << line << '\n';
		}

	}
	return { ss[0].str() , ss[1].str() };
}

unsigned int Shader::CompileShader(const unsigned int& Type, const std::string& Source)
{
	unsigned int id = glCreateShader(Type);

	const char* src = Source.c_str();
	glShaderSource(id, 1, &src, nullptr);

	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int lenght;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
		char* message = (char*)_malloca(lenght * sizeof(char));

		glGetShaderInfoLog(id, lenght, &lenght, message);

		glDeleteShader(id);

		std::string error =
			"Failed to compile " +
			std::string(Type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") +
			" Shader!\n\n" +
			std::string(message);
		throw std::runtime_error(error);

		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& VertexShader, const std::string& FragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, VertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);


	glAttachShader(program, vs);
	glAttachShader(program, fs); // add the vertex and fragment shade to the program 

	glLinkProgram(program);
	glValidateProgram(program);

	int CheckResult;

	glGetProgramiv(program, GL_LINK_STATUS, &CheckResult);

	if (CheckResult == GL_FALSE)
	{
		GLint length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

		// Allocate memory
		char* message = (char*)_malloca(length * sizeof(char));

		// Retrieve the error message
		glGetProgramInfoLog(program, length, &length, message);

		std::string error =
			"Failed to Link Shader Program! \n"  "Program ID " +
			std::to_string(program) +
			"\n Error - " + message;

		glDeleteProgram(program);
		throw std::runtime_error(error);
	}

	glDeleteShader(vs);
	glDeleteShader(fs);


	return program;
}