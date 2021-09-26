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

void Renderer::Draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader)
{
	shader.Bind();
	va.Bind();
	ib.Bind();

	//GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear(glm::vec4 color)
{
	GLCall(glClearColor(color.x, color.y, color.z, color.w));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}