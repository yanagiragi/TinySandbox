#pragma once

#include "Component.hpp"

namespace TinySandbox
{
	class RotateAxis : public Component
	{
		public:
			void Start() override;
			
			void Update() override;
			
			void OnGUI() override;
		
		private:
			
			float m_incrementAngle;
		
	};
}
