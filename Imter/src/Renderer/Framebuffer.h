#pragma once

#include "Core/Base.h"

#include <vector>
#include <set>

struct FramebufferSpecification
{
	uint32_t Width = 0, Height = 0;
	// FramebufferFormat Format = 
	uint32_t Samples = 1;

	bool SwapChainTarget = false;
};

struct PixelInfo 
{
	float ObjectID;
	float DrawID;
	float PrimID;

	PixelInfo()
	{
		ObjectID = 0.0f;
		DrawID = 0.0f;
		PrimID = 0.0f;
	}
};

struct PixelInfoCmp
{
	bool operator()(const PixelInfo& lhs, const PixelInfo& rhs) const
	{
		return lhs.DrawID < rhs.DrawID;
	}
};

enum class FramebufferType
{
	default,
	RGBFloat32
};

class Framebuffer
{
public:
	Framebuffer(const FramebufferSpecification& spec, FramebufferType type = FramebufferType::default);
	~Framebuffer();

	void Invalidate();

	void Bind();
	void Unbind();

	void Resize(uint32_t width, uint32_t height);

	uint32_t GetColorAttachmentRendererID() const { return m_ColorAttachment; }

	const FramebufferSpecification& GetSpecification() const { return m_Specification; }
	std::set<PixelInfo, PixelInfoCmp> ReadPixel(unsigned int x, unsigned int y, unsigned int width = 1, unsigned int height = 1);

private:
	uint32_t m_RendererID = 0;
	uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
	FramebufferSpecification m_Specification;
	FramebufferType m_Type;
};
