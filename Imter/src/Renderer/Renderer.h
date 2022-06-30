#pragma once

#include "Core/Base.h"

#include "Renderer/Camera.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Renderer/OpenGLRendererAPI.h"

class Renderer
{
public:
	static void Init();
	static void Shutdown();
		
	static void OnWindowResize(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

	static void BeginScene(Camera& camera);
	static void EndScene();

	static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

	static void SetClearColor(const glm::vec4& color);
	static void Clear();
	static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0);

private:
	struct SceneData
	{
		glm::mat4 ViewProjectionMatrix;
	};

	static Scope<SceneData> s_SceneData;
	inline static Scope<OpenGLRendererAPI> s_RendererAPI = CreateScope<OpenGLRendererAPI>();
};
