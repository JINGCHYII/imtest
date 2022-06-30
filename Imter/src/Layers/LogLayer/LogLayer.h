#pragma once

#include "Core/Layer.h"

#include "Core/Application.h"

#include "ImGui/UI/imnode/imnodes.h"
#include <imgui.h>


#define IM_TRACE(...)	static_cast<LogLayer*>(Application::Get().GetLayer("LogLayer"))->Im_Trace(__VA_ARGS__)
#define IM_INFO(...)	static_cast<LogLayer*>(Application::Get().GetLayer("LogLayer"))->Im_Info(__VA_ARGS__)
#define IM_WARN(...)	static_cast<LogLayer*>(Application::Get().GetLayer("LogLayer"))->Im_Warn(__VA_ARGS__)
#define IM_ERROR(...)	static_cast<LogLayer*>(Application::Get().GetLayer("LogLayer"))->Im_Error(__VA_ARGS__)
#define IM_FATAL(...)	static_cast<LogLayer*>(Application::Get().GetLayer("LogLayer"))->Im_Critical(__VA_ARGS__)


enum class LogType
{
	Trace,
	Info,
	Warn,
	Error,
	Critical
};

struct LogInfo
{
	LogType type;
	int offset;
};

class LogLayer : public Layer
{

#define LOG(Type) 	void LogLayer::Im_##Type(const char* fmt, ...) { \
	int old_size = Buf.size(); \
	va_list args; \
	va_start(args, fmt); \
	Buf.appendfv(fmt, args); \
	va_end(args); \
	if (*(Buf.end() - 1) != '\n') Buf.append("\n"); \
	for (int new_size = Buf.size(); old_size < new_size; old_size++) \
		if (Buf[old_size] == '\n') \
			LineOffsets.push_back({ LogType::##Type, old_size + 1 }); \
	}

public:

	LogLayer();

	void Clear();
	void AddLog(LogType type, const char* fmt, ...);
	void Draw(const char* title, bool* p_open = NULL);


	LOG(Trace);
	LOG(Info);
	LOG(Warn);
	LOG(Error);
	LOG(Critical);


	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Event& event) override;


	

private:
	ImGuiTextBuffer     Buf;
	ImGuiTextFilter     Filter;
	ImVector<LogInfo>   LineOffsets;        // Index to lines offset. We maintain this with AddLog() calls, allowing us to have a random access on lines
	bool                AutoScroll;     // Keep scrolling if already at the bottom

};