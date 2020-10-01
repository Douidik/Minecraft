#include "VertexBuffer.h"
#include "ShaderProgram.h"

Ref<VertexBuffer> VertexBuffer::Create(const void *data, size_t size, GLenum usage, Layout layout)
{
	return CreateRef<VertexBuffer>(data, size, usage, layout);
}

Ref<VertexBuffer> VertexBuffer::Create(Layout layout, GLenum usage)
{
	return CreateRef<VertexBuffer>(layout, usage);
}

VertexBuffer::VertexBuffer(const void *data, size_t size, GLenum usage, Layout layout)
	: Buffer(data, size, GL_ARRAY_BUFFER, usage), m_Layout(layout)
{ }

VertexBuffer::VertexBuffer(Layout layout, GLenum usage)
	: Buffer(GL_ARRAY_BUFFER, usage), m_Layout(layout)
{ }

void VertexBuffer::Bind()
{
	m_Layout.Bind();
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::UnBind()
{
	m_Layout.UnBind();
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
