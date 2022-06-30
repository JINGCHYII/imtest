#include "EditorLayer.h"
#include "Core/Application.h"
#include "Core/Input.h"
#include <imgui.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <set>

EditorLayer::EditorLayer()
	: Layer("EditorLayer"), m_CameraController(1280.0f / 720.0f)
{
}

void EditorLayer::OnAttach()
{	
	FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_Framebuffer = CreateRef<Framebuffer>(fbSpec);
	m_PickingFramebuffer = CreateRef<Framebuffer>(fbSpec, FramebufferType::RGBFloat32);

	m_SquareVA = CreateRef<VertexArray>();

	/*float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0,0,-1,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0,0,-1,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0,0,-1,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0,0,-1,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0,0,-1,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0,0,-1,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0,0,1,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0,0,1,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0,0,1,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0,0,1,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0,0,1,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0,0,1,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1,0,0,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1,0,0,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1,0,0,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1,0,0,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1,0,0,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1,0,0,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1,0,0,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1,0,0,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1,0,0,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1,0,0,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1,0,0,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1,0,0,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0,-1,0,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0,-1,0,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0,-1,0,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0,-1,0,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0,-1,0,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0,-1,0,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0,1,0,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0,1,0,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0,1,0,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0,1,0,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0,1,0,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0,1,0,
	};

	Ref<VertexBuffer> squareVB = CreateRef<VertexBuffer>(vertices, sizeof(vertices));
	squareVB->SetLayout({
		{ ShaderDataType::Float3, "aPos" },
		{ ShaderDataType::Float2, "aTexCoord" },
		{ ShaderDataType::Float3, "aNormal" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[] = {
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,
		12, 13, 14,
		15, 16, 17,
		18, 19, 20,
		21, 22, 23,
		24, 25, 26,
		27, 28, 29,
		30, 31, 32,
		33, 34, 35,
	};
	Ref<IndexBuffer> squareIB = CreateRef<IndexBuffer>(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIB);*/

	auto readFile = [](const std::string& filePath)
	{
		std::string ret;
		if (std::ifstream is{ filePath, std::ios::binary | std::ios::ate }) {
			auto size = is.tellg();
			ret = std::string(size, '\0'); // construct string to stream size
			is.seekg(0);
			if (is.read(&ret[0], size))
				std::cout << ret << '\n';
		}
		return ret;
	};

	std::string vertex_shader_text = readFile("assets/shaders/camera.vs");
	std::string fragment_shader_text = readFile("assets/shaders/camera.fs");
	m_Shader = CreateRef<Shader>("VertexPosColor", vertex_shader_text, fragment_shader_text);
	
	std::string layout_vertex_shader_text = readFile("assets/shaders/geometry_shader.vs");
	std::string layout_fragment_shader_text = readFile("assets/shaders/geometry_shader.fs");
	std::string layout_geometry_shader_text = readFile("assets/shaders/geometry_shader.gs");
	m_LayoutShader = CreateRef<Shader>("LayoutColor", layout_vertex_shader_text, layout_fragment_shader_text, layout_geometry_shader_text);
	
	std::string picking_vertex_shader_text = readFile("assets/shaders/picking.vs");
	std::string picking_fragment_shader_text = readFile("assets/shaders/picking.fs");
	m_PickingShader = CreateRef<Shader>("PickingS", picking_vertex_shader_text, picking_fragment_shader_text);
	
	std::string highlight_vertex_shader_text = readFile("assets/shaders/highlight.vs");
	std::string highlight_fragment_shader_text = readFile("assets/shaders/highlight.fs");
	m_HighLightShader = CreateRef<Shader>("PickingC", highlight_vertex_shader_text, highlight_fragment_shader_text);


	//m_Shader->Bind();
	//m_Shader->UploadUniformInt("texture1", 0);
	//m_CheckerboardTexture = CreateRef<Texture>("assets/textures/doge2.jpeg");


	Model ourModel("assets/models/cube.obj");


	auto createVAO = [&](Model model)
	{
		std::vector<Ref<VertexArray>> vaos;

		int i = -1;
		for (const auto& mesh : model.meshes)
		{
			i++;
			Ref<VertexArray> vao = CreateRef<VertexArray>();
			std::vector<float> vecs;
			std::vector<uint32_t> indexs;
			
			//for (const auto& vec : mesh.vertices)
			//{
			//	vecs.push_back(vec.Position.x);
			//	vecs.push_back(vec.Position.y);
			//	vecs.push_back(vec.Position.z);
			//	vecs.push_back(vec.Normal.x);
			//	vecs.push_back(vec.Normal.y);
			//	vecs.push_back(vec.Normal.z);
			//}
			//for (const auto& index : mesh.indices)
			//{
			//	indexs.push_back(index);
			//}

			int j = 0;
			int cnt = -1;
			for (int x = 0; x < mesh.indices.size(); x++)
			{
				const auto& vec = mesh.vertices[mesh.indices[x]];
				vecs.push_back(vec.Position.x);
				vecs.push_back(vec.Position.y);
				vecs.push_back(vec.Position.z);
				vecs.push_back(vec.Normal.x);
				vecs.push_back(vec.Normal.y);
				vecs.push_back(vec.Normal.z);
				vecs.push_back((float)i);
				cnt++;
				if (cnt == 3)
				{
					cnt = 0;
					j++;
				}
				vecs.push_back((float)j);
				vecs.push_back(0);

				indexs.push_back(x);
			}


			Ref<VertexBuffer> squareVB = CreateRef<VertexBuffer>(vecs.data(), vecs.size() * sizeof(float));
			squareVB->SetLayout({
				{ ShaderDataType::Float3, "aPos" },
				{ ShaderDataType::Float3, "aNormal" },
				{ ShaderDataType::Float3, "aIndex" }
				});
			vao->AddVertexBuffer(squareVB);
			Ref<IndexBuffer> squareIB = CreateRef<IndexBuffer>(indexs.data(), indexs.size());
			vao->SetIndexBuffer(squareIB);

			vaos.push_back(vao);

			m_Models.push_back({ vecs, indexs });
		}

		return vaos;
	};

	m_Models = Model2Holder(ourModel);
	m_VertexArrays = Holder2VAO(m_Models);

	//m_VertexArrays = createVAO(ourModel);
}

void EditorLayer::OnDetach()
{
}

void EditorLayer::OnUpdate(Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	// Resize
	if (FramebufferSpecification spec = m_Framebuffer->GetSpecification();
		m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
		(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
	{
		m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_PickingFramebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		//m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
	}

	glm::mat4 projection;
	if (m_ViewportSize.x != 0 && m_ViewportSize.y != 0)
	{
		if (ortho)
		{
			static float ortho_width = 8, ortho_height = 6, ortho_near = -1, ortho_far = 100;

			if (Input::IsKeyPressed(Key::W))
			{
				ortho_width -= 0.1;
				ortho_height -= 0.1 / 4 * 3;
			}
			else if (Input::IsKeyPressed(Key::S))
			{
				ortho_width += 0.1;
				ortho_height += 0.1 / 4 * 3;
			}
			//projection = glm::ortho(-8.0f, 8.0f, -6.0f, 6.0f, -1.f, 100.0f);
			projection = glm::ortho(-ortho_width, ortho_width, -ortho_height, ortho_height, ortho_near, ortho_far);
		}
		else
			projection = glm::perspective(glm::radians(45.f), (float)m_ViewportSize.x / (float)m_ViewportSize.y, 0.1f, 100.0f);
	}

	auto renderObj = [&](Ref<Shader> shader)
	{
		shader->UploadUniformMat4("projection", projection);
		shader->UploadUniformMat4("view", m_CameraController.GetCamera().GetViewMatrix());
		shader->UploadUniformFloat3("viewNormal", m_CameraController.GetCamera().Front);

		glm::vec3 cubePositions[] = 
		{
			glm::vec3(0.0f,  0.0f,  0.0f),
			//glm::vec3(2.0f,  5.0f, -15.0f),
			//glm::vec3(-1.5f, -2.2f, -2.5f),
			//glm::vec3(-3.8f, -2.0f, -12.3f),
			//glm::vec3(2.4f, -0.4f, -3.5f),
			//glm::vec3(-1.7f,  3.0f, -7.5f),
			//glm::vec3(1.3f, -2.0f, -2.5f),
			//glm::vec3(1.5f,  2.0f, -2.5f),
			//glm::vec3(1.5f,  0.2f, -1.5f),
			//glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		for (unsigned int i = 0; i < sizeof(cubePositions) / sizeof(glm::vec3); i++)
		{
			glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader->UploadUniformMat4("model", model);

			for (const auto vao : m_VertexArrays)
			{
				//std::cout << vao->m_RendererID << '\n';
				Renderer::Submit(shader, vao, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));
			}
		}
	};
	
	{
		Renderer2D::ResetStats();
		m_PickingFramebuffer->Bind();
		Renderer::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
		Renderer::Clear();

		m_PickingShader->Bind();
		renderObj(m_PickingShader);
		m_PickingShader->Unbind();

		m_PickingFramebuffer->Unbind();
	}

	{
		Renderer2D::ResetStats();
		m_Framebuffer->Bind();
		Renderer::SetClearColor({ 0.1f, 0.8f, 0.1f, 1 });
		Renderer::Clear();

		//glPolygonMode(GL_FRONT, GL_LINE);

		m_Shader->Bind();

		static std::set<uint32_t> selectedIdxs;
		static bool isSelecting = false;

		for (const auto& pixelInfo : pixelInfos)
		{
			if (pixelInfo.PrimID != 0 && (uint32_t)pixelInfo.ObjectID < m_VertexArrays.size())
			{
				//m_Shader->UploadUniformFloat("selectedId", pixelInfo.DrawID);

				uint32_t drawId = (uint32_t)pixelInfo.DrawID;
				for (int i = 0; i < 3; ++i)
				{
					uint32_t idx = (3 * drawId + i) * 9 + 8;
					if (!selectedIdxs.count(idx))
					{
						selectedIdxs.insert(idx);
						m_Models[(uint32_t)pixelInfo.ObjectID].vecs[idx] = 1;
						m_VertexArrays = Holder2VAO(m_Models);
						isSelecting = true;
					}
				}
			}
			else
			{
				if (isSelecting)
				{
					for (auto idx : selectedIdxs)
						m_Models[0].vecs[idx] = 0;
					selectedIdxs.clear();
					m_VertexArrays = Holder2VAO(m_Models);
					isSelecting = false;
				}
			}
		} 

		//std::cout << selectionX1 << " " << selectionX2 << "  " << selectionY1 << " " << selectionY2 << '\n';
		m_Shader->UploadUniformFloat2("selectionX", glm::vec2(selectionX1, selectionX2));
		m_Shader->UploadUniformFloat2("selectionY", glm::vec2(selectionY1, selectionY2));
		
		renderObj(m_Shader);
		m_Shader->Unbind();

		if (showGrid)
		{
			m_LayoutShader->Bind();
			renderObj(m_LayoutShader);
			m_LayoutShader->Unbind();
		}

		//std::cout << pixelInfo.PrimID << " "
		//	<< pixelInfo.ObjectID << " "
		//	<< pixelInfo.DrawID << '\n';

		//if (pixelInfo.PrimID != 0 && (uint32_t)pixelInfo.ObjectID < m_VertexArrays.size())
		//{			
		//	m_HighLightShader->Bind(); 
		//	m_HighLightShader->UploadUniformMat4("projection", projection);
		//	m_HighLightShader->UploadUniformMat4("view", m_CameraController.GetCamera().GetViewMatrix());
		//	m_HighLightShader->UploadUniformFloat3("viewNormal", m_CameraController.GetCamera().Front);

		//	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		//	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//	model = glm::rotate(model, glm::radians(0.f), glm::vec3(1.0f, 0.3f, 0.5f));
		//	m_HighLightShader->UploadUniformMat4("model", model);
		//	
		//	Ref<VertexArray> vao = m_VertexArrays[(uint32_t)pixelInfo.ObjectID];
		//	
		//	vao->Bind();
		//	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (const GLvoid*)((uint32_t)pixelInfo.DrawID * 3 * sizeof(float)));
		//	vao->Unbind();
		//	
		//	m_HighLightShader->Unbind();
		//}

		m_Framebuffer->Unbind();
	}
}

void EditorLayer::OnImGuiRender()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows, 
			// which we can't undo at the moment without finer window depth/z control.
			//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);1
			if (ImGui::MenuItem("Exit")) Application::Get().Close();
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	ImGui::Begin("Settings");

	ImGui::Checkbox("ortho", &ortho);
	ImGui::Checkbox("show grid", &showGrid);
	ImGui::Checkbox("picking mode", &pickingMode);

	ImGui::End();


	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	ImGui::Begin("Viewport");

	m_ViewportFocused = ImGui::IsWindowFocused();
	m_ViewportHovered = ImGui::IsWindowHovered();
	Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

	ImGuiWindow* Window = ImGui::GetCurrentWindow();
	auto pos = Window->DC.CursorPos;

	ImVec2 mousePos = ImGui::GetIO().MousePos;
	ImVec2 mouseinview = (mousePos - pos) / viewportPanelSize;

	static ImVec2 mouseDownPos, mouseUpPos;
	static bool firstMouseDown = true;

	bool hovered = mouseinview.x >= 0. && mouseinview.x <= 1. &&
		mouseinview.y >= 0. && mouseinview.y <= 1.;
	if (hovered && ImGui::IsMouseDown(0) && pickingMode)
	{
		if (firstMouseDown)
		{
			firstMouseDown = false;
			mouseDownPos = ImVec2{ (mousePos - pos).x, m_ViewportSize.y - (mousePos - pos).y };
		}
		else
		{
		}
		//std::cout << "down:" << mouseDownPos.x << " " << mouseDownPos.y << '\n';
	}
	if (hovered && ImGui::IsMouseReleased(0) && pickingMode)
	{
		firstMouseDown = true;
		mouseUpPos = ImVec2{ (mousePos - pos).x, m_ViewportSize.y - (mousePos - pos).y };

		float x1 = std::min(mouseDownPos.x, mouseUpPos.x);
		float x2 = std::max(mouseDownPos.x, mouseUpPos.x);
		float y1 = std::min(mouseDownPos.y, mouseUpPos.y);
		float y2 = std::max(mouseDownPos.y, mouseUpPos.y);

		std::cout << x1 << " " << x2 << "  " << y1 << " " << y1 << '\n';

		selectionX1 = x1 / m_ViewportSize.x * 2 - 1;
		selectionX2 = x2 / m_ViewportSize.x * 2 - 1;
		selectionY1 = y1 / m_ViewportSize.y * 2 - 1;
		selectionY2 = y2 / m_ViewportSize.y * 2 - 1;

		//pixelInfos = m_PickingFramebuffer->ReadPixel(x1, y1, std::max(x2 - x1, (uint32_t)1), std::max(y2 - y1, (uint32_t)1));
		std::cout << "up:" << mouseUpPos.x << " " << mouseUpPos.y << '\n';
	}

	if (hovered && ImGui::IsMouseClicked(0))
	{
		if (!pickingMode)
		{
			isPlaying = true;
			m_CameraController.mouseMoveEnable = true;
			m_CameraController.firstMouse = true;

			MouseVisToggleEvent e(false);
			Application::Get().OnEvent(e);
		}
		else
		{
			pixelInfos = m_PickingFramebuffer->ReadPixel((mousePos - pos).x, m_ViewportSize.y - (mousePos - pos).y);
		}
	}
	if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape)))
	{
		isPlaying = false;
		m_CameraController.mouseMoveEnable = false;

		MouseVisToggleEvent e(true);
		Application::Get().OnEvent(e);
	}

	uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
	ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

	ImGui::End();
	ImGui::PopStyleVar();
}

void EditorLayer::OnEvent(Event& e)
{
	m_CameraController.OnEvent(e);

	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(EditorLayer::OnMouseScrolledEvent));
}


bool EditorLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
{
	return true;
}



std::vector<ModelHolder> EditorLayer::Model2Holder(Model model)
{
	std::vector<ModelHolder> ret;

	int i = -1;
	for (const auto& mesh : model.meshes)
	{
		i++;
		Ref<VertexArray> vao = CreateRef<VertexArray>();
		std::vector<float> vecs;
		std::vector<uint32_t> indexs;

		//for (const auto& vec : mesh.vertices)
		//{
		//	vecs.push_back(vec.Position.x);
		//	vecs.push_back(vec.Position.y);
		//	vecs.push_back(vec.Position.z);
		//	vecs.push_back(vec.Normal.x);
		//	vecs.push_back(vec.Normal.y);
		//	vecs.push_back(vec.Normal.z);
		//}
		//for (const auto& index : mesh.indices)
		//{
		//	indexs.push_back(index);
		//}

		int j = 0;
		int cnt = -1;
		for (int x = 0; x < mesh.indices.size(); x++)
		{
			const auto& vec = mesh.vertices[mesh.indices[x]];
			vecs.push_back(vec.Position.x);
			vecs.push_back(vec.Position.y);
			vecs.push_back(vec.Position.z);
			vecs.push_back(vec.Normal.x);
			vecs.push_back(vec.Normal.y);
			vecs.push_back(vec.Normal.z);
			vecs.push_back((float)i);
			cnt++;
			if (cnt == 3)
			{
				cnt = 0;
				j++;
			}
			vecs.push_back((float)j);
			vecs.push_back(0);

			indexs.push_back(x);
		}

		ret.push_back({ vecs, indexs });
	}

	return ret;
}

std::vector<Ref<VertexArray>> EditorLayer::Holder2VAO(const std::vector<ModelHolder>& holders)
{
	std::vector<Ref<VertexArray>> vaos;

	for (const auto& holder : holders)
	{
		Ref<VertexArray> vao = CreateRef<VertexArray>();

		auto vecs = holder.vecs;
		auto indexs = holder.indexs;

		Ref<VertexBuffer> squareVB = CreateRef<VertexBuffer>(vecs.data(), vecs.size() * sizeof(float));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "aPos" },
			{ ShaderDataType::Float3, "aNormal" },
			{ ShaderDataType::Float3, "aIndex" }
			});
		vao->AddVertexBuffer(squareVB);
		Ref<IndexBuffer> squareIB = CreateRef<IndexBuffer>(indexs.data(), indexs.size());
		vao->SetIndexBuffer(squareIB);

		vaos.push_back(vao);
	}

	return vaos;
}