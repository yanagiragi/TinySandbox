#pragma once

#include "MeshRenderer.hpp"
#include "BaseMaterial.hpp"

namespace TinySandbox
{
	class BRDFLutGenerator : public MeshRenderer
	{
		public:
			BRDFLutGenerator();
			~BRDFLutGenerator();

			static void SetupFrameBufferAndRenderBuffer(unsigned int _resolution);
			static unsigned int Generate(int _resolution);
			static BRDFLutGenerator* Instance();

			void InitializeFrameBufferObjects(GraphicsAPI* m_api);

		private:
			BaseMaterial* m_brdLutfProgram;
			unsigned int m_frameBufferObject;
			unsigned int m_renderBufferObject;
			static BRDFLutGenerator* m_instance;
	};
}