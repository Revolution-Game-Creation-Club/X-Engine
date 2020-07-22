#include "Xpch.h"
#include <glm/gtc/matrix_transform.hpp>
#include "XEngine/GraphicsSystem/Shader.h"
#include "XEngine/GraphicsSystem/VertexArray.h"
#include "XEngine/GraphicsSystem/Renderer/Renderer2D.h"
#include "XEngine/GraphicsSystem/Renderer/RenderCommand.h"
namespace XEngine
{
	struct Renderer2DData
	{
		Ref<VertexArray> vertexArray;
		Ref<Shader> textureShader;
		Ref<Texture2D> whiteTexture;
	};
	static Renderer2DData* rendererData;
	void Renderer2D::Init()
	{
		rendererData = new Renderer2DData();
		rendererData->vertexArray = VertexArray::Create();
		float squareVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Ref<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout
		({ 
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"}
		});
		rendererData->vertexArray->AddVertexBuffer(squareVB);
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		rendererData->vertexArray->SetIndexBuffer(squareIB);
		rendererData->whiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		rendererData->whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
		rendererData->textureShader = Shader::Create("Assets/Shaders/FlatColor.glsl");
		rendererData->textureShader = Shader::Create("Assets/Shaders/Texture.glsl");
		rendererData->textureShader->Bind();
		rendererData->textureShader->SetInt("u_Texture", 0);
	}
	void Renderer2D::Shutdown()
		{ delete rendererData; }
	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		rendererData->textureShader->Bind();
		rendererData->textureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}
	void Renderer2D::EndScene() {}
	// Draw Quad Vector2(Flat Color)
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
		{ DrawQuad({position.x, position.y, 0.0}, size, color); }
	// Draw Quad Vector3(Flat Color)
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		rendererData->textureShader->SetFloat4("u_Color", color);
		rendererData->whiteTexture->Bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		rendererData->textureShader->SetMat4("u_Transform", transform);
		rendererData->vertexArray->Bind();
		RenderCommand::DrawIndexed(rendererData->vertexArray);
	}
	// Draw Quad Vector2(Texture)
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture)
		{ DrawQuad({position.x, position.y, 0.0}, size, texture); }
	// Draw Quad Vector3(Texture)
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture)
	{
		rendererData->textureShader->SetFloat4("u_Color", glm::vec4(1.0f));
		texture->Bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		rendererData->textureShader->SetMat4("u_Transform", transform);
		rendererData->vertexArray->Bind();
		RenderCommand::DrawIndexed(rendererData->vertexArray);
	}
}