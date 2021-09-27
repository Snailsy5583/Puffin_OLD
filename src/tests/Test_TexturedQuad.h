#pragma once

#include "Test.h"

#include "Renderer.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include "Shader.h"
#include "Texture.h"

#include <imgui/imgui.h>

namespace Test
{

	class Test_TexturedQuad : public Test
	{
	public:
		Test_TexturedQuad();
		~Test_TexturedQuad();

		void OnUpdate(float deltaTime) override;
		void OnRender(Renderer& renderer) override;
		void OnImGUIRender() override;

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

		glm::vec4 m_ClearColor;
		glm::vec4 m_Color;
		const char * m_TexturePath;
		Texture m_Texture;

	};

}
