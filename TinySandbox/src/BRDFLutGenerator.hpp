#pragma once

#include "MeshRenderer.hpp"
#include "BaseMaterial.hpp"

namespace TinySandbox
{
	class BRDFLutGenerator : public MeshRenderer
	{
		public:
			BRDFLutGenerator(int _resolution);
			~BRDFLutGenerator();

			static unsigned int GetLutID();

		private:
			static void SetupFrameBufferAndRenderBuffer();
			static unsigned int Generate(int _resolution);
			static BRDFLutGenerator* Instance();
			static void SetResolution(int _resolution);

			void InitializeFrameBufferObjects(GraphicsAPI* m_api);
			BaseMaterial* m_brdLutfProgram;
			unsigned int m_frameBufferObject;
			unsigned int m_renderBufferObject;
			unsigned int m_brdfLutTextureId;
			int m_resolution;
			static BRDFLutGenerator* m_instance;
	};
}