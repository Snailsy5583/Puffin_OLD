#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

static bool CheckErrors(const char * file, const char * function, int line)
{
	while (GLenum err = glGetError())
	{
		std::cout << "[OpenGL Error] " << err << "--" << function << " in " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

static void ClearErrors() { while (glGetError() != 0); }

#ifndef ASSERT
	#define ASSERT(x) if (!(x)) __debugbreak();

	#ifdef DEBUG
#define GLCall(x) ClearErrors(); x; ASSERT(CheckErrors(__FILE__, #x, __LINE__))
	#else
		#define GLCall(x) x
	#endif
#endif