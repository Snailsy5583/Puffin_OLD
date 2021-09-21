#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Renderer.h"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

enum class UniformType
{
	INT_1, INT_2, INT_3, INT_4,
	FLOAT_1, FLOAT_2, FLOAT_3, FLOAT_4
};

class Shader
{
public:
	Shader(const std::string & source);
	~Shader();

	int CreateShader();

	ShaderProgramSource ParseShader();

	static unsigned int CompileShader(unsigned int type, const std::string & source);

	void SetUniform(UniformType type, const char * name, float _1, float _2=0, float _3=0, float _4=0);

	void Bind();
	void UnBind();

	void DeleteShader();

private:
	std::string& path;
	ShaderProgramSource source;
	unsigned int id;

public:
	inline ShaderProgramSource GetSource() const { return source; }
	inline unsigned int GetID() const { return id; }
};