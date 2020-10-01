#ifndef MINECRAFT_BUFFER_H
#define MINECRAFT_BUFFER_H

/*
 * Interface Class providing a wrapper for
 * OpenGL Buffers
 */

class Buffer
{
public:
	Buffer(const void *data, size_t size, GLenum target, GLenum usage);
	Buffer(GLenum target, GLenum usage);
	~Buffer();

	virtual void SetData(const void *data, size_t size);

	virtual void Bind() = 0;
	virtual void UnBind() = 0;

	int GetParameter(GLenum parameter) const;

private:
	void Generate();

protected:
	GLuint m_RendererID;

	GLenum m_Target;
	GLenum m_Usage;
};

#endif //MINECRAFT_BUFFER_H
