#pragma once

#include <string>
#include <unordered_map>

struct ShaderProgramSources
{
	std::string mVertexSources;
	std::string mFragmentSources;
};

class Shader
{
private:
	unsigned int mRendererID;
	std::string mFilePath;
	std::unordered_map<std::string, int> mUniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
private:
	int GetUniformLocation(const std::string& name);
	ShaderProgramSources ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};