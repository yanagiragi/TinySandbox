#include "BRDFLutGenerator.hpp"

#include "Quad.hpp"

TinySandbox::BRDFLutGenerator* TinySandbox::BRDFLutGenerator::m_instance = nullptr;

namespace TinySandbox
{
	BRDFLutGenerator::BRDFLutGenerator()
	{
		this->SetMesh(new Quad());
		
		m_frameBufferObject = 4294967294; // magic number to mean "un-initialized"
		m_renderBufferObject = 4294967294;

		// TODO
		// m_brdLutfProgram = nullptr;
	}

	BRDFLutGenerator::~BRDFLutGenerator()
	{
		m_frameBufferObject = 4294967294; // magic number to mean "un-initialized"
		m_renderBufferObject = 4294967294;
	}

	BRDFLutGenerator* BRDFLutGenerator::Instance()
	{
		if (BRDFLutGenerator::m_instance == nullptr) {
			m_instance = new BRDFLutGenerator();
		}
		return m_instance;
	}

	void BRDFLutGenerator::SetupFrameBufferAndRenderBuffer(unsigned int _resolution) {
		GraphicsAPI* m_api = GraphicsAPI::GetAPI();

		if (BRDFLutGenerator::Instance()->m_frameBufferObject == 4294967294 || BRDFLutGenerator::Instance()->m_renderBufferObject == 4294967294) {
			BRDFLutGenerator::Instance()->InitializeFrameBufferObjects(m_api);

			m_api->BindFrameBuffer(GraphicsAPI_DataType::FRAMEBUFFER, BRDFLutGenerator::Instance()->m_frameBufferObject);
			m_api->BindRenderBuffer(GraphicsAPI_DataType::RENDERBUFFER, BRDFLutGenerator::Instance()->m_renderBufferObject);

			m_api->SetRenderBuffer(GraphicsAPI_DataType::RENDERBUFFER, GraphicsAPI_DataType::DEPTH_COMPONENT24, _resolution, _resolution);
			m_api->AttachRenderBufferToFrameBuffer(
				GraphicsAPI_DataType::FRAMEBUFFER, 
				GraphicsAPI_DataType::DEPTH_ATTACHMENT,
				GraphicsAPI_DataType::RENDERBUFFER,
				BRDFLutGenerator::Instance()->m_renderBufferObject
			);

			m_api->UnbindFrameBuffer(GraphicsAPI_DataType::FRAMEBUFFER);
		}
	};

	unsigned int BRDFLutGenerator::Generate(int _resolution)
	{
		GraphicsAPI* m_api = GraphicsAPI::GetAPI();
		unsigned int brdfTexId;

		// 1. Setup FBO Objects
		BRDFLutGenerator::SetupFrameBufferAndRenderBuffer(_resolution);

		// 2. Setup Texture
		m_api->GenerateTextures(&brdfTexId, 1);
		m_api->BindTexture(GraphicsAPI_DataType::TEXTURE_2D, brdfTexId);
		m_api->SetTexture2D(GraphicsAPI_DataType::TEXTURE_2D, 0, GraphicsAPI_DataType::RG16F, _resolution, _resolution, 0, GraphicsAPI_DataType::RG, GraphicsAPI_DataType::FLOAT, 0);
		m_api->SetTextureParameter(GraphicsAPI_DataType::TEXTURE_2D, GraphicsAPI_DataType::TEXTURE_WRAP_S, GraphicsAPI_DataType::CLAMP_TO_EDGE);
		m_api->SetTextureParameter(GraphicsAPI_DataType::TEXTURE_2D, GraphicsAPI_DataType::TEXTURE_WRAP_T, GraphicsAPI_DataType::CLAMP_TO_EDGE);

		m_api->SetTextureParameter(GraphicsAPI_DataType::TEXTURE_2D, GraphicsAPI_DataType::TEXTURE_MIN_FILTER, GraphicsAPI_DataType::LINEAR);
		m_api->SetTextureParameter(GraphicsAPI_DataType::TEXTURE_2D, GraphicsAPI_DataType::TEXTURE_MAG_FILTER, GraphicsAPI_DataType::LINEAR);

		// 3. Bilt brdfLutProgram
		m_api->BindFrameBuffer(GraphicsAPI_DataType::FRAMEBUFFER, BRDFLutGenerator::Instance()->m_frameBufferObject);
		m_api->SetViewport(0, 0, _resolution, _resolution);

		m_api->SetFrameBuffer2D(GraphicsAPI_DataType::FRAMEBUFFER, GraphicsAPI_DataType::COLOR_ATTACHMENT0, GraphicsAPI_DataType::TEXTURE_2D, brdfTexId, 0);

		BRDFLutGenerator::Instance()->m_brdLutfProgram->Use();

		m_api->ClearScreenColor();
		m_api->ClearScreenDepth();

		m_api->BindVertexArray(BRDFLutGenerator::Instance()->m_VAO);
		m_api->DrawArrays(GraphicsAPI_DataType::TRIANGLES, BRDFLutGenerator::Instance()->m_mesh->vertex.size());

		// Cleanup
		BRDFLutGenerator::Instance()->m_brdLutfProgram->Unuse();
		m_api->UnbindFrameBuffer(GraphicsAPI_DataType::FRAMEBUFFER);
		m_api->UnbindVertexArray();
		m_api->UnbindProgram();

		return brdfTexId;
	}

	void BRDFLutGenerator::InitializeFrameBufferObjects(GraphicsAPI* m_api)
	{
		m_api->GenerateFrameBuffers(&m_frameBufferObject, 1);
		m_api->GenerateRenderBuffers(&m_renderBufferObject, 1);
	}
}