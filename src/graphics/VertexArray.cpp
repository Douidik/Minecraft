
#include "VertexArray.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

Ref<VertexArray> VertexArray::Create()
{
	return CreateRef<VertexArray>();
}

VertexArray::VertexArray()
	: m_RendererID(0), m_StrideOffset(0)
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));

	for(auto vertexBuffer : m_VertexBuffers)
		vertexBuffer->Bind();

	m_IndexBuffer->Bind();
}

void VertexArray::UnBind() const
{
	for(auto vertexBuffer : m_VertexBuffers)
		vertexBuffer->UnBind();

	m_IndexBuffer->UnBind();
	GLCall(glBindVertexArray(0));
}

void VertexArray::AddIndexBuffer(Ref<IndexBuffer> indexBuffer)
{
	m_IndexBuffer = indexBuffer;
}

void VertexArray::AddVertexBuffer(Ref<VertexBuffer> vertexBuffer)
{
	GLCall(glBindVertexArray(m_RendererID));
	vertexBuffer->Bind();

	Layout &layout = vertexBuffer->GetLayout();
	size_t stride = m_StrideOffset + layout.GetStride();

	for(const auto &attribute : layout.GetAttributes())
	{
		switch (attribute.type)
		{
		case GL_BYTE:
		case GL_UNSIGNED_BYTE:
		case GL_SHORT:
		case GL_UNSIGNED_SHORT:
		case GL_INT:
		case GL_UNSIGNED_INT:
		{
			GLCall(glVertexAttribIPointer(attribute.index, attribute.count, attribute.type, stride, (const void *)attribute.offset));
			break;
		}
		case GL_DOUBLE:
		{
			GLCall(glVertexAttribLPointer(attribute.index, attribute.count, attribute.type, stride, (const void *)attribute.offset));
			break;
		}
		default:
		{
			GLCall(glVertexAttribPointer(attribute.index, attribute.count, attribute.type, attribute.normalized, stride, (const void *)attribute.offset));
			break;
		}
		}
	}

	m_StrideOffset += stride;
	m_VertexBuffers.push_back(vertexBuffer);
}
