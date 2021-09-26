#pragma once

#include <GL/glew.h>
#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"

#include <glm/glm.hpp>

bool CheckErrors(const char * file, const char * function, int line);

void ClearErrors();

class Renderer
{
public:
	void Draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader);

	void Clear(glm::vec4 color);
};

//void DrawIndices();

#define ASSERT(x) if (!(x)) __debugbreak();

#ifdef DEBUG
	#define GLCall(x) ClearErrors(); x; ASSERT(CheckErrors(__FILE__, #x, __LINE__))
#else
	#define GLCall(x) x
#endif