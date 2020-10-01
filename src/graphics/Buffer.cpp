
#include "Buffer.h"
#include "util/Utility.h"

Buffer::Buffer(const void *data, size_t size, GLenum target, GLenum usage)
	: m_Target(target), m_Usage(usage)
{
	Generate();
	SetData(data, size);
}

Buffer::Buffer(GLenum target, GLenum usage)
	: m_Target(target), m_Usage(usage)
{
	Generate();
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void Buffer::SetData(const void *data, size_t size)
{
	GLCall(glBindBuffer(m_Target, m_RendererID));
	GLCall(glBufferData(m_Target, size, data, m_Usage));
}

void Buffer::Generate()
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(m_Target, m_RendererID));
}

int Buffer::GetParameter(GLenum parameter) const
{
	int value = 0;

	glBindBuffer(m_Target, m_RendererID);
	glGetBufferParameteriv(m_Target, parameter, &value);

	return value;
}