#ifndef MINECRAFT_VERTEXBUFFER_H
#define MINECRAFT_VERTEXBUFFER_H

#include "Layout.h"
#include "Buffer.h"

class VertexBuffer : public Buffer
{
public:
	static Ref<VertexBuffer> Create(const void *data, size_t size, GLenum usage, Layout layout);
	static Ref<VertexBuffer> Create(Layout layout, GLenum usage);

	VertexBuffer(const void *data, size_t size, GLenum usage, Layout layout);
	VertexBuffer(Layout layout, GLenum usage);

	void Bind() override;
	void UnBind() override;

	inline Layout &GetLayout()
	{
		return m_Layout;
	}

private:
	Layout m_Layout;
};

#endif //MINECRAFT_VERTEXBUFFER_H