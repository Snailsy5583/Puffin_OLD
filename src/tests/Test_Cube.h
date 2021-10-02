#pragma once

#include "Test.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace Test
{
	class Test_Cube : public Test
	{
	public:
		Test_Cube();
		~Test_Cube();

		void OnUpdate(float deltaTime) override;
		void OnRender(Renderer & renderer) override;
		void OnImGUIRender() override;

	private:
		float m_Positions[24] = 
		{
			-0.5f, -0.5f, -0.5f, // --- / 0 
			 0.5f, -0.5f, -0.5f, // +-- / 1 
			 0.5f,  0.5f, -0.5f, // ++- / 2 
			-0.5f,  0.5f, -0.5f, // -+- / 3 
			-0.5f, -0.5f,  0.5f, // --+ / 4 
			 0.5f, -0.5f,  0.5f, // +-+ / 5 
			 0.5f,  0.5f,  0.5f, // +++ / 6 
			-0.5f,  0.5f,  0.5f, // -++ / 7 
		};
		unsigned int m_Indices[36] = 
		{
			4, 5, 6, 6, 7, 4,
			5, 1, 2, 2, 6, 5,
			1, 0, 3, 3, 2, 1,
			0, 4, 7, 7, 2, 0,
			7, 6, 2, 2, 3, 7,
			0, 1, 5, 5, 4, 0
		};

		VertexArray m_VA;
		VertexBufferLayout m_Layout;

		VertexBuffer m_VB;
		IndexBuffer m_IB;

		Shader m_Shader;

		glm::vec4 m_Color;

		glm::mat4 m_Model;
		glm::mat4 m_View;
		glm::mat4 m_Projection;
		glm::mat4 m_MVP;

		float m_Rotation;
		float m_RotationSpeed;

		float m_FOV;
		glm::vec3 m_Position;
	};
};

