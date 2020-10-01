#include "mc.pch"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Ref<Image> Image::Create(const fs::path &path)
{
	return CreateRef<Image>(path);
}

Image::Image(const fs::path &path)
{
	data = stbi_load(path.c_str(), &width, &height, &bpp, 0);
	MC_ASSERT_WARN(data, "Failed to load image from: {}", path.string());
}

GLenum Image::GetGLFormat() const
{
	switch(bpp)
	{
	case 1: return GL_RED;
	case 2: return GL_RG;
	case 3: return GL_RGB;
	case 4: return GL_RGBA;
	default: MC_ASSERT(0, "OpenGL doesn't support this format, bpp: {}", bpp); return 0;
	}
}

Image::~Image()
{
	stbi_image_free(data);
}

Ref<Texture> Texture::Create(Ref<Image> image)
{
	return CreateRef<Texture>(image);
}

Ref<Texture> Texture::Create()
{
	return CreateRef<Texture>();
}

Texture::Texture(Ref<Image> image)
{
	Generate();
	SetData(image);
}

Texture::Texture()
{
	Generate();
}

void Texture::Bind(GLint slot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::UnBind()
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::Generate()
{
	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::SetData(Ref<Image> image)
{
	MC_ASSERT(*image, "Image data is not valid");

	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	GLCall(glTexImage2D(GL_TEXTURE_2D,
		0,
		image->GetGLFormat(),
		image->width,
		image->height,
		0,
		image->GetGLFormat(),
		GL_UNSIGNED_BYTE,
		image->data));

	glGenerateMipmap(GL_TEXTURE_2D);
	Setup(image->width, image->height);
}

void Texture::Setup(int width, int height)
{
	int mipmapsLevel = ceil(log(std::max(width, height))) + 1;
	mipmapsLevel = 1;
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipmapsLevel));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
}