#pragma once

#include "Entity.hpp"

namespace TinySandbox {

    class Windows 
    {
        public:

			Windows()
			{

			}

			Windows(Entity&& _mainLoop)
			{
				mainLoop = new Entity(_mainLoop);
			}

			~Windows()
			{
				delete mainLoop;
			}
			
			virtual bool ShouldClose() = 0;
			virtual void MainLoop() = 0;

		//protected:
			Entity* mainLoop;
    };
 
}

