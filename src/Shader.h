#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const std::string & source);
	~Shader();

	int CreateShader();

	ShaderProgramSource ParseShader();

	static unsigned int CompileShader(unsigned int type, const std::string & source);

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