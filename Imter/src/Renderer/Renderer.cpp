#include "Renderer.h"

#include "Renderer/Renderer2D.h"

Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

void Renderer::Init()
{
	s_RendererAPI->Init();
}

void Renderer::Shutdown()
{
	Renderer2D::Shutdown();
}

void Renderer::OnWindowResize(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	glViewport(x, y, width, height);
}

void Renderer::BeginScene(Camera& camera)
{
	s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
{
	shader->Bind();
	/*shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
	shader->SetMat4("u_Transform", transform);
*/
	vertexArray->Bind();
	s_RendererAPI->DrawIndexed(vertexArray);
	vertexArray->Unbind();
}


void Renderer::SetClearColor(const glm::vec4& color)
{
	s_RendererAPI->SetClearColor(color);
}

void Renderer::Clear()
{
	s_RendererAPI->Clear();
}

void Renderer::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count)
{
	s_RendererAPI->DrawIndexed(vertexArray, count);
}