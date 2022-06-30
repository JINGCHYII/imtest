#pragma once

#include "Core/Layer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/Camera.h"
#include "Renderer/Texture.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Framebuffer.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"

#include "learnopengl/model.h"

#include <set>

struct ModelHolder
{
	std::vector<float> vecs;
	std::vector<uint32_t> indexs;
};

class EditorLayer : public Layer
{
public:
	EditorLayer();
	virtual ~EditorLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Event& e) override;

	bool OnMouseScrolledEvent(MouseScrolledEvent& e);

	std::vector<ModelHolder> Model2Holder(Model model);
	std::vector<Ref<VertexArray>> Holder2VAO(const std::vector<ModelHolder>& holders);

private:
	CameraController m_CameraController;

	Ref<VertexArray> m_SquareVA;

	Ref<Framebuffer> m_Framebuffer;
	Ref<Framebuffer> m_PickingFramebuffer;

	std::vector<Ref<VertexArray>> m_VertexArrays;
	Ref<Shader> m_Shader;
	Ref<Shader> m_LayoutShader;
	Ref<Shader> m_PickingShader;
	Ref<Shader> m_HighLightShader;

	Ref<Texture> m_CheckerboardTexture;

	bool m_ViewportFocused = false, m_ViewportHovered = false;
	glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

	//glm::mat4x4 m_Model = glm::mat4x4(1.0f), m_View = glm::mat4x4(1.0f), m_Projection = glm::mat4x4(1.0f), mvp = glm::mat4x4(1.0f);

	bool isPlaying = false;
	bool ortho = true;
	bool showGrid = true;
	bool pickingMode = false;

	std::set<PixelInfo, PixelInfoCmp> pixelInfos; //tmp

	std::vector<ModelHolder> m_Models;

	float selectionX1, selectionX2, selectionY1, selectionY2;
};

