#pragma once

// Namespace
#include "Test.h"

// Rendering
#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <glm/glm.hpp>

namespace Test
{
	class Test_Quad : public Test
	{
	public:
		Test_Quad();
		Test_Quad(const char* shader_path, glm::vec4 _color);
		~Test_Quad();

		void OnUpdate(float deltaTime) override;
		void OnRender(Renderer& renderer) override;
		void OnImGUIRender() override;
		void OnImGUIRender(glm::vec4 & clear_color);

	private:
		float m_Positions[8] =
		{
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};;

		unsigned int m_Indices[6] =
		{
			0, 1, 2,
			2, 3, 0
		};

		VertexArray m_VA;
		VertexBufferLayout m_Layout;

		VertexBuffer m_VB;
		IndexBuffer m_IB;
		
		Shader m_Shader;

		glm::vec4 m_Color;
	};
}

