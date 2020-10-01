#ifndef MINECRAFT_TEXTURE_H
#define MINECRAFT_TEXTURE_H

struct Image
{
	static Ref<Image> Create(const fs::path &path);

	Image(const fs::path &path);
	~Image();
	ubyte *data;
	int width, height, bpp;

	GLenum GetGLFormat() const;

	/* Returns if the image data is valid */
	operator bool()
	{
		return data != nullptr;
	}
};

class Texture
{
public:
	static Ref<Texture> Create(Ref<Image> image);
	static Ref<Texture> Create();

	Texture(Ref<Image> image);
	Texture();

	void SetData(Ref<Image> image);

	virtual void Bind(GLint slot = 0);
	virtual void UnBind();

protected:
	void Setup(int width, int height);
	void Generate();
	GLuint m_RendererID;
};

#endif //MINECRAFT_TEXTURE_H
