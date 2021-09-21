#include "Shader.h"

Shader::Shader(const std::string & source) : path((std::string &) source)
{
    this->source = ParseShader();
    this->id = CreateShader();
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(id));
}

ShaderProgramSource Shader::ParseShader()
{
    std::ifstream stream(path);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

int Shader::CreateShader()
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, source.VertexSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, source.FragmentSource);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string & source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char * src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char * message = (char *) malloc(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

void Shader::SetUniform(UniformType type, const char * name, float _1, float _2, float _3, float _4)
{
    GLCall(int location = glGetUniformLocation(id, name));
    ASSERT(location != -1);
    switch (type)
    {
    case UniformType::INT_1:
        GLCall(glUniform1i(location, (int) _1));
        break;
    case UniformType::INT_2:
        GLCall(glUniform2i(location, (int) _1, (int) _2));
        break;
    case UniformType::INT_3:
        GLCall(glUniform3i(location, (int) _1, (int) _2, (int) _3));
        break;
    case UniformType::INT_4:
        GLCall(glUniform4i(location, (int) _1, (int) _2, (int) _3, (int) _4));
        break;
    case UniformType::FLOAT_1:
        GLCall(glUniform1f(location, _1));
        break;
    case UniformType::FLOAT_2:
        GLCall(glUniform2f(location, _1, _2));
        break;
    case UniformType::FLOAT_3:
        GLCall(glUniform3f(location, _1, _2, _3));
        break;
    case UniformType::FLOAT_4:
        GLCall(glUniform4f(location, _1, _2, _3, _4));
        break;
    }
}

void Shader::Bind() { GLCall(glUseProgram(id)); }

void Shader::UnBind() { GLCall(glUseProgram(0)); }

void Shader::DeleteShader() { GLCall(glDeleteProgram(id)); }