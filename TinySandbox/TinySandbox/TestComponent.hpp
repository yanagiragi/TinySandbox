#pragma once

#include "Component.hpp"

#include <iostream>

namespace TinySandbox
{
	class TestComponent : public Component
	{
		public:
			void Start() override
			{
				std::cout << "Start!" << std::endl;
			}

			void Update() override
			{
				std::cout << "Update!" << std::endl;
			}

			void OnGUI() override
			{
				std::cout << "OnGUI!" << std::endl;
			}
	};
}
