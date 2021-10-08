#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <vector>

#include <glm/glm.hpp>

#include "Window.h"

class Renderer;

namespace Test
{
	class Test
	{
	public:
		Test() { }
		virtual ~Test() { }

		virtual void OnUpdate(float deltaTime) { }
		virtual void OnUpdate(float deltaTime, Input * input) { }
		virtual void OnRender() { }
		virtual void OnRender(Renderer& renderer) { }
		virtual void OnImGUIRender() { }
		virtual void OnImGUIRender(glm::vec4 clear_color) { }
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test *& currentTestPtr);

		void OnImGUIRender() override;

		template<typename T>
		void RegisterTest(const std::string & name)
		{
			std::cout << "Registering Test " << name << std::endl;
			m_Tests.push_back(std::make_pair(name, [] () { return new T(); }));
		}

	private:
		Test * & m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test * ()>>> m_Tests;
	};
}