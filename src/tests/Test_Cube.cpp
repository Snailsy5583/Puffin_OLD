#include "Test_Cube.h"

#include <glm/gtc/matrix_transform.hpp>

#include <imgui/imgui.h>

namespace Test
{
	Test_Cube::Test_Cube()
		:	m_VA(), m_Layout(), m_VB(m_Positions, sizeof(m_Positions)),
			m_IB(m_Indices, sizeof(m_Indices) / sizeof(unsigned int)),
			m_Shader("res/shaders/Basic_NoTexture.shader"), m_Color(1, 1, 1, 1),
			m_Position(0.f, 0.f, -5.f),
			m_LightPosition(0.f, 0.f, 0.f),
			m_Model(glm::translate(glm::mat4(1.f), m_Position)),
			m_View(glm::lookAt(glm::vec3(0), { 0.f, 0.f, -5.f }, glm::vec3(0, 1, 0))),
			m_FOV(90.f), m_Projection(glm::perspective(glm::radians(m_FOV), 16.f/9, 0.1f, 500.f)),
			m_Rotation(0.f),
			m_RotationSpeed(0.0f),
			m_CamSpeed(0.1f),
			m_IsLooking(false)
	{
		m_Layout.Push<float>(3);
		m_VA.AddBuffer(m_VB, m_Layout);
		m_Shader.Bind();
		m_Shader.SetUniform(UniformType::FLOAT_4, "u_Color", m_Color.x, m_Color.y, m_Color.z, m_Color.w);

		m_Shader.SetUniformMat4("u_Model", m_Model);
		m_Shader.SetUniformMat4("u_View", m_View);
		m_Shader.SetUniformMat4("u_Projection", m_Projection);

		m_Shader.SetUniform(UniformType::FLOAT_3, "u_LightPos", m_LightPosition.x, m_LightPosition.y, m_LightPosition.z);


		m_View = glm::lookAt(glm::vec3(0), { 0.f, 0.f, -5.f }, glm::vec3(0, 1, 0));
	}
	
	Test_Cube::~Test_Cube()
	{
	}
	
	void Test_Cube::OnUpdate(float deltaTime, Input * input)
	{
		m_Shader.Bind();
		m_Shader.SetUniform(UniformType::FLOAT_4, "u_Color", m_Color.x, m_Color.y, m_Color.z, m_Color.w);
		m_Projection = glm::perspective(glm::radians(m_FOV), 16.f / 9, 0.1f, 500.f);

		if (input->GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT))
		{
			input->SetMouseMode(false);
			if (input->GetKeyPressed(GLFW_KEY_W))
				m_CamLoc.z += m_CamSpeed;
			if (input->GetKeyPressed(GLFW_KEY_A))
				m_CamLoc.x += m_CamSpeed;
			if (input->GetKeyPressed(GLFW_KEY_S))
				m_CamLoc.z -= m_CamSpeed;
			if (input->GetKeyPressed(GLFW_KEY_D))
				m_CamLoc.x -= m_CamSpeed;
			if (input->GetKeyPressed(GLFW_KEY_Q))
				m_CamLoc.y += m_CamSpeed;
			if (input->GetKeyPressed(GLFW_KEY_E))
				m_CamLoc.y -= m_CamSpeed;

			if (!m_IsLooking)
			{
				m_IsLooking = true;
				m_StartCamRot = glm::vec2(input->GetMousePosition().x, input->GetMousePosition().y);
			}

			m_CamRot = m_EndCamRot - m_StartCamRot + glm::vec2(input->GetMousePosition().x, input->GetMousePosition().y);
			//m_EndCamRot = {0.f, 0.f};
		}
		else if (m_IsLooking)
		{
			m_IsLooking = false;
			m_EndCamRot = m_CamRot;

			input->SetMouseMode(true);
		}

		glm::mat4 CamRotX = glm::rotate(glm::mat4(1.f), glm::radians(m_CamRot.x/7.f), glm::vec3(0.f, 1.f, 0.f));
		glm::mat4 CamRotY = glm::rotate(glm::mat4(1.f), glm::radians(m_CamRot.y/7.f), glm::vec3(glm::vec4(1.f, 0.f, 0.f, 1.f) * CamRotX));
		glm::mat4 CamRotT = CamRotX * CamRotY;

		glm::vec3 ForVec = {CamRotT[0][2], CamRotT[1][2], CamRotT[2][2]};

		//glm::vec3 RotCamLoc = ForVec * (glm::length(m_CamLoc));
		
		glm::mat4 CamTran = glm::translate(glm::mat4(1.f), m_CamLoc);

		m_View = CamRotT * CamTran * 1.f;
		//m_View = glm::lookAt(glm::vec3(CamTran * glm::vec4(1.f)), glm::vec3(CamRotT * glm::vec4(1.f)), {0.f, 1.f, 0.f});
		// 
		//m_View *= glm::translate(glm::mat4(1.f), glm::vec3(CamRotX*CamRotY*glm::vec4(m_CamLoc, 1.f)));

		//m_View *= glm::translate(glm::mat4(1.f), m_CamLoc);

		m_Model =	glm::translate(glm::mat4(1.f), m_Position) * 
					glm::rotate(glm::mat4(1.f), glm::radians(m_Rotation), glm::vec3(1.f, 0.f, 1.f));
		m_Rotation += m_RotationSpeed;

		m_Shader.SetUniformMat4("u_Model", m_Model);
		m_Shader.SetUniformMat4("u_View", m_View);
		m_Shader.SetUniformMat4("u_Projection", m_Projection);

		m_Shader.SetUniform(UniformType::FLOAT_3, "u_LightPos", m_LightPosition.x, m_LightPosition.y, m_LightPosition.z);
	}
	
	void Test_Cube::OnRender(Renderer & renderer)
	{
		renderer.Draw(m_VA, m_IB, m_Shader);
	}
	
	void Test_Cube::OnImGUIRender()
	{
		ImGui::ColorEdit4("Cube Color: ", (float*) &m_Color);
		ImGui::DragFloat("Rotation Speed: ", &m_RotationSpeed, 0.005f, -10.f, 10.f);
		ImGui::DragFloat3("Cube Position: ", &m_Position.x, 0.1f, 0.f, -50.f);
		ImGui::DragFloat3("Light Position: ", &m_LightPosition.x, 0.1f, 0.f, -50.f);

		ImGui::DragFloat("FOV: ", &m_FOV, 1.f, 0.f, 360.f);

		ImGui::DragFloat("Cam Speed: ", &m_CamSpeed, 0.001f, 0.f, 0.5f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
};