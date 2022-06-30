#pragma once

#include <string>

#include "Core/Base.h"
#include <glad/glad.h>

class Texture
{
public:
	Texture(uint32_t width, uint32_t height);
	Texture(const std::string& path);
	~Texture();

	uint32_t GetWidth() const { return m_Width; }
	uint32_t GetHeight() const { return m_Height; }
	uint32_t GetRendererID() const { return m_RendererID; }

	void SetData(void* data, uint32_t size);
	void SetData(void* data, uint32_t w, uint32_t h);
	unsigned char* GetData() const { return m_data; }

	void Bind(uint32_t slot = 0) const;

	bool operator==(const Texture& other) const 
	{
		return m_RendererID == ((Texture&)other).m_RendererID;
	}

private:
	std::string m_Path;
	uint32_t m_Width, m_Height;
	uint32_t m_RendererID;
	GLenum m_InternalFormat, m_DataFormat;

	unsigned char* m_data;
};
