#pragma once

namespace TinySandbox
{
	class Component 
	{
		public:
			virtual void Start() = 0;
			virtual void Update() = 0;
			virtual void OnGUI() = 0;

			virtual void OnRender() {}; // not force override
	};
}