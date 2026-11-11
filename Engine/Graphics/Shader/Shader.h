#pragma once

#include <string>
#include <unordered_map>
#include "../../Vendor/glm/glm.hpp"


struct ShaderProgramSource
{
	std::string VertexShader;
	std::string FragmentShader;
};

class Shader
{
public:
	Shader(const std::string& filePath);
	~Shader();

	unsigned int GetRendererID() const { return m_RendererID; }

	void Bind() const;
	void Unbind() const;
	void SetUniform1i(const std::string& name, int value);

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

	void SetUniform1f(const std::string& name, float value);

private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	std::unordered_map<std::string, int> m_uniformLocationCache;
	ShaderProgramSource source;


	int GetUniformLocation(const std::string& name);
	ShaderProgramSource ParseShader(const std::string& FilePath);
	unsigned int CompileShader(const unsigned int& Type, const std::string& Source);
	unsigned int CreateShader(const std::string& VertexShader, const std::string& FragmentShader);
};