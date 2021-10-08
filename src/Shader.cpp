#include "Shader.h"
#include "Renderer.h"

Shader::Shader(const std::string & source) : m_Path((std::string &) source)
{
    this->m_Source = ParseShader();
    this->m_RendererID = CreateShader();
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

ShaderProgramSource Shader::ParseShader()
{
    std::ifstream stream(m_Path);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2
    };

    std::string line;
    std::stringstream ss[3];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
            else if (line.find("geometry") != std::string::npos)
                type = ShaderType::GEOMETRY;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str(), ss[2].str() };
}

int Shader::CreateShader()
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, m_Source.VertexSource);
    unsigned int gs = CompileShader(GL_GEOMETRY_SHADER, m_Source.GeometrySource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, m_Source.FragmentSource);

    GLCall(glAttachShader(program, vs));
    if (gs != 0) { GLCall(glAttachShader(program, gs)); }
    GLCall(glAttachShader(program, fs));

    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    if (gs == 0) { GLCall(glDeleteShader(gs)); }
    GLCall(glDeleteShader(fs));

    return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string & source)
{
    if (source.empty())
        return 0;

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
    switch (type)
    {
    case UniformType::INT_1:
        GLCall(glUniform1i(GetUniformLocation(name), (int) _1));
        break;
    case UniformType::INT_2:
        GLCall(glUniform2i(GetUniformLocation(name), (int) _1, (int) _2));
        break;
    case UniformType::INT_3:
        GLCall(glUniform3i(GetUniformLocation(name), (int) _1, (int) _2, (int) _3));
        break;
    case UniformType::INT_4:
        GLCall(glUniform4i(GetUniformLocation(name), (int) _1, (int) _2, (int) _3, (int) _4));
        break;
    case UniformType::FLOAT_1:
        GLCall(glUniform1f(GetUniformLocation(name), _1));
        break;
    case UniformType::FLOAT_2:
        GLCall(glUniform2f(GetUniformLocation(name), _1, _2));
        break;
    case UniformType::FLOAT_3:
        GLCall(glUniform3f(GetUniformLocation(name), _1, _2, _3));
        break;
    case UniformType::FLOAT_4:
        GLCall(glUniform4f(GetUniformLocation(name), _1, _2, _3, _4));
        break;
    }
}

void Shader::SetUniformMat4(const char * name, glm::mat4 & matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]))
}

int Shader::GetUniformLocation(const char * name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_RendererID, name));
    if (location == -1)
        std::cout << name << " does not exist!" << std::endl;

    m_UniformLocationCache[name] = location;
    return location;
}


void Shader::Bind() const { GLCall(glUseProgram(m_RendererID)); }

void Shader::UnBind() const { GLCall(glUseProgram(0)); }

void Shader::DeleteShader() { GLCall(glDeleteProgram(m_RendererID)); }