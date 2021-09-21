#pragma once

#include <GL/glew.h>
//#include "IndexBuffer.h"

bool CheckErrors(const char * file, const char * function, int line);

void ClearErrors();

//void DrawIndices();

#define ASSERT(x) if (!(x)) __debugbreak();

#ifdef DEBUG
	#define GLCall(x) ClearErrors(); x; ASSERT(CheckErrors(__FILE__, #x, __LINE__))
#else
	#define GLCall(x) x
#endif