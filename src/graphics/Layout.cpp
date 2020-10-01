#include "Layout.h"
#include "graphics/ShaderProgram.h"
#include "graphics/VertexBuffer.h"
#include "util/Utility.h"

Layout::Layout(std::initializer_list<Attribute> attributes)
	: m_Attributes(attributes)
{
	size_t offset = 0;

	for(auto &attribute : m_Attributes)
	{
		attribute.offset = offset;
		offset += SizeOfGLType(attribute.type) * attribute.count;
	}

	m_Stride = offset;
}

void Layout::Bind() const
{
	for(const auto &a : m_Attributes)
	{
		GLCall(glEnableVertexAttribArray(a.index));
	}
}

void Layout::UnBind() const
{
	for(const auto &a : m_Attributes)
	{
		GLCall(glDisableVertexAttribArray(a.index));
	}
}
