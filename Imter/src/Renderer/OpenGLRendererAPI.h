#pragma once

#include "Core/Base.h"
#include "Renderer/VertexArray.h"

#include "glm/glm.hpp"

class OpenGLRendererAPI
{
public:
	~OpenGLRendererAPI() = default;

	void Init();
	void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

	void SetClearColor(const glm::vec4& color);
	void Clear();

	void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0);
};
