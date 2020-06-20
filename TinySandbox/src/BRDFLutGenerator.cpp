#include "BRDFLutGenerator.hpp"

#include "Quad.hpp"
#include "BRDFLutMaterial.hpp"
#include "Windows.hpp"

TinySandbox::BRDFLutGenerator* TinySandbox::BRDFLutGenerator::m_instance = nullptr;

namespace TinySandbox
{
	BRDFLutGenerator::BRDFLutGenerator(int _resolution)
	{
		this->SetMesh(new Quad());
		
		m_frameBufferObject = 4294967294; // magic number to mean "un-initialized"
		m_renderBufferObject = 4294967294;
		m_brdfLutTextureId = 4294967294;

		m_resolution = _resolution;

		m_brdLutfProgram = new BRDFLutMaterial();
	}

	BRDFLutGenerator::~BRDFLutGenerator()
	{
		m_frameBufferObject = 4294967294; // magic number to mean "un-initialized"
		m_renderBufferObject = 4294967294;
	}

	BRDFLutGenerator* BRDFLutGenerator::Instance()
	{
		if (BRDFLutGenerator::m_instance == nullptr) {
			m_instance = new BRDFLutGenerator(128); // default resolution = 128
		}
		return m_instance;
	}

	void BRDFLutGenerator::SetResolution(int _resolution)
	{
		if (BRDFLutGenerator::Instance()->m_resolution != _resolution)
		{
			BRDFLutGenerator::Instance()->m_brdfLutTextureId = BRDFLutGenerator::Generate(_resolution);
		}

		BRDFLutGenerator::Instance()->m_resolution = _resolution;
	}

	unsigned int BRDFLutGenerator::GetLutID()
	{
		if (BRDFLutGenerator::Instance()->m_brdfLutTextureId == 4294967294)
		{
			BRDFLutGenerator::Instance()->m_brdfLutTextureId = BRDFLutGenerator::Generate(BRDFLutGenerator::Instance()->m_resolution);
		}

		return BRDFLutGenerator::Instance()->m_brdfLutTextureId;
	}

	void BRDFLutGenerator::SetupFrameBufferAndRenderBuffer() {
		GraphicsAPI* m_api = GraphicsAPI::GetAPI();
		const int _resolution = BRDFLutGenerator::Instance()->m_resolution;

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
		BRDFLutGenerator::SetupFrameBufferAndRenderBuffer();

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

		Windows* window = Windows::GetInstance();
		m_api->SetViewport(0, 0, window->GetWidth(), window->GetHeight());

		return brdfTexId;
	}

	void BRDFLutGenerator::InitializeFrameBufferObjects(GraphicsAPI* m_api)
	{
		m_api->GenerateFrameBuffers(&m_frameBufferObject, 1);
		m_api->GenerateRenderBuffers(&m_renderBufferObject, 1);
	}
}