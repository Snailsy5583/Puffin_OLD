#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>

#include <glm/glm.hpp>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
	std::string GeometrySource;
};

enum class UniformType
{
	INT_1, INT_2, INT_3, INT_4,
	FLOAT_1, FLOAT_2, FLOAT_3, FLOAT_4,

	MAT_4
};

class Shader
{
public:
	Shader(const std::string & source);
	~Shader();

	int CreateShader();

	ShaderProgramSource ParseShader();

	static unsigned int CompileShader(unsigned int type, const std::string & source);

	void SetUniform(UniformType type, const char * name, float _1=0, float _2=0, float _3=0, float _4=0);
	void SetUniformMat4(const char * name, glm::mat4 & matrix);

	int GetUniformLocation(const char * name);

	void Bind() const;
	void UnBind() const;

	void DeleteShader();

private:
	std::string& m_Path;
	ShaderProgramSource m_Source;
	unsigned int m_RendererID;
	std::unordered_map<const char *, int> m_UniformLocationCache;

public:
	inline ShaderProgramSource GetSource() const { return m_Source; }
	inline unsigned int GetID() const { return m_RendererID; }
};