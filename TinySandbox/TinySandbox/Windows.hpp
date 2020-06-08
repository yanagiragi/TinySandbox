#pragma once

#include "Scene.hpp"

namespace TinySandbox {

    class Windows 
    {
        public:

			Windows()
			{

			}

			Windows(Scene&& _mainLoop)
			{
				mainScene = new Scene(_mainLoop);
			}

			~Windows()
			{
				delete mainScene;
			}

			void SetScene(Scene* _scene)
			{
				mainScene = _scene;
			}
			
			virtual bool ShouldClose() = 0;
			virtual void Loop() = 0;

		protected:
			Scene* mainScene;
    };
 
}

