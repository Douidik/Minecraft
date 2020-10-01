
#include "IndexBuffer.h"
#include "util/Utility.h"

Ref<IndexBuffer> IndexBuffer::Create(const void *data, size_t size, GLenum type, GLenum usage)
{
	return CreateRef<IndexBuffer>(data, size, type, usage);
}

Ref<IndexBuffer> IndexBuffer::Create(GLenum type, GLenum usage)
{
	return CreateRef<IndexBuffer>(type, usage);
}

IndexBuffer::IndexBuffer(const void *data, size_t size, GLenum type, GLenum usage)
	: Buffer(data, size, GL_ELEMENT_ARRAY_BUFFER, usage), m_Type(type)
{ }

IndexBuffer::IndexBuffer(GLenum type, GLenum usage)
	: Buffer(GL_ELEMENT_ARRAY_BUFFER, usage), m_Type(type)
{ }

void IndexBuffer::Bind()
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::UnBind()
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::SetData(const void *data, size_t size)
{
	m_Count = size / SizeOfGLType(m_Type);

	Buffer::SetData(data, size);
}
