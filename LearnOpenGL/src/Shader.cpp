#include "renderer.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


Shader::Shader(const std::string& filepath)
	:mFilePath(filepath), mRendererID(0)
{
    ShaderProgramSources sources = ParseShader(filepath);
    mRendererID = CreateShader(sources.mVertexSources, sources.mFragmentSources);
}
Shader::~Shader()
{
    GLCall(glDeleteProgram(mRendererID));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(mRendererID));
}
void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

// Set uniforms

void Shader::SetUniform1f(const std::string& name, float value)
{
    GLCall(glUniform1f(GetUniformLocation(name), value));
}
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (mUniformLocationCache.find(name) != mUniformLocationCache.end())
    {
        return mUniformLocationCache[name];
    }
    GLCall(int location = glGetUniformLocation(mRendererID, name.c_str()));
    if (location == -1)
    {
        std::cout << "Warning: uniform '" << name << "' doesn`t exist!" << std::endl;
    }
    else
    {
        mUniformLocationCache[name] = location;
    }
    return (unsigned int)location;
}

enum class ShaderType
{
    NONE = -1, VERTEX = 0, FRAGMENT = 1
};

ShaderProgramSources Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    ShaderProgramSources sps = { ss[0].str(), ss[1].str() };
    return sps;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        if (type == GL_VERTEX_SHADER) printf("vertexShader\n");
        if (type == GL_FRAGMENT_SHADER) printf("fragmentShader\n");
        printf("Failed to compile shader!\n");
        printf("%s\n", message);

        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));

    GLint program_linked;
    GLCall(glGetProgramiv(program, GL_LINK_STATUS, &program_linked));
    std::cout << "Program link status: " << program_linked << std::endl;
    if (program_linked != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        GLCall(glGetProgramInfoLog(program, 1024, &log_length, message));
        std::cout << "Failed to link program" << std::endl;
        std::cout << message << std::endl;
    }

    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}