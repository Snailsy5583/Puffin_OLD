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
		float m_Positions[16] =
		{
			-0.5f, -0.5f,	 0.f,  0.f,
			 0.5f, -0.5f,	 1.f,  0.f,
			 0.5f,  0.5f,	 1.f,  1.f,
			-0.5f,  0.5f,	 0.f,  1.f
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
		Texture m_Texture;

		glm::mat4 m_Model;
		glm::mat4 m_View;
		glm::mat4 m_Projection;
		glm::mat4 m_MVP;

	};

}
