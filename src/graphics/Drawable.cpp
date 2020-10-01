#include "Drawable.h"

Drawable::Drawable(Layout layout, GLenum indexType, GLenum usage)
	: m_IsSubmitted(false)
{
	Generate(layout, indexType, usage);
}

Drawable::~Drawable()
{
	Destroy();
}

void Drawable::Generate(Layout layout, GLenum indexType, GLenum usage)
{
	m_Layout = layout;

	m_VertexArray = VertexArray::Create();

	m_VertexBuffer = VertexBuffer::Create(m_Layout, usage);
	m_VertexArray->AddVertexBuffer(m_VertexBuffer);

	m_IndexBuffer = IndexBuffer::Create(indexType, usage);
	m_VertexArray->AddIndexBuffer(m_IndexBuffer);

	m_Transform = Transform::Create();
	m_RenderRequest = { m_VertexArray, m_Transform };
}

void Drawable::Destroy()
{
	m_VertexBuffer.reset();
	m_IndexBuffer.reset();
	m_VertexArray.reset();
}