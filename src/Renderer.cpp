#include "Renderer.h"

#include <iostream>

bool CheckErrors(const char * file, const char * function, int line)
{
	while (GLenum err = glGetError())
	{
		std::cout << "[OpenGL Error] " << err << "--" << function << " in " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

void ClearErrors() { while (glGetError() != 0); }