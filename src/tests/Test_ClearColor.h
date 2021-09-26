#pragma once

#include "Test.h"

namespace Test
{
	class Test_ClearColor : public Test
	{ 
	public:
		Test_ClearColor();
		~Test_ClearColor();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnRender(Renderer& renderer) override;
		void OnImGUIRender() override;

	private:
		float m_ClearColor[4];

	};
}

