#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VertexBuffer
{
public:
	VertexBuffer(const void * data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void SetData(const void * data, unsigned int size);

private:
	unsigned int m_RendererID;
	unsigned int m_Size;

public:
	inline unsigned int GetSize() const { return m_Size; }
};