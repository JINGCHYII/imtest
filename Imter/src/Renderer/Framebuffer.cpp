#include "Framebuffer.h"

#include <glad/glad.h>

static const uint32_t s_MaxFramebufferSize = 8192;

Framebuffer::Framebuffer(const FramebufferSpecification& spec, FramebufferType type)
	: m_Specification(spec), m_Type(type)
{
	Invalidate();
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &m_RendererID);
	glDeleteTextures(1, &m_ColorAttachment);
	glDeleteTextures(1, &m_DepthAttachment);
}

void Framebuffer::Invalidate()
{
	if (m_RendererID)
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthAttachment);
	}

	glCreateFramebuffers(1, &m_RendererID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
	glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
	if (m_Type == FramebufferType::default)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	else if (m_Type == FramebufferType::RGBFloat32)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, m_Specification.Width, m_Specification.Height, 0, GL_RGB, GL_FLOAT, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
	glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	glViewport(0, 0, m_Specification.Width, m_Specification.Height);
}

void Framebuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Resize(uint32_t width, uint32_t height)
{
	if (width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize)
	{
		return;
	}
	m_Specification.Width = width;
	m_Specification.Height = height;

	Invalidate();
}

std::set<PixelInfo, PixelInfoCmp> Framebuffer::ReadPixel(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_RendererID);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	std::vector<PixelInfo> Pixels(width * height);
	glReadPixels(x, y, width, height, GL_RGB, GL_FLOAT, &Pixels[0]);
	glReadBuffer(GL_NONE);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

	std::set<PixelInfo, PixelInfoCmp> ret;
	for (const auto& pixel : Pixels)
		ret.insert(pixel);

	return ret;
}