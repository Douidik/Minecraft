#ifndef MINECRAFT_DRAWABLE_H
#define MINECRAFT_DRAWABLE_H

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "Renderer.h"

#include "util/Utility.h"

template<class Vertex, typename IndexType>
struct DrawableData
{
	std::vector<Vertex> vertices;
	std::vector<IndexType> indices;
};

class Drawable
{
public:
	RenderRequest GetRenderRequest() const
	{
		return m_RenderRequest;
	}

	Ref<Transform> GetTransform() const
	{
		return m_Transform;
	}

	void SetTransform(Ref<Transform> transform)
	{
		m_Transform = transform;
	}

	bool IsSubmitted() const
	{
		return m_IsSubmitted;
	}

protected:
	Drawable(Layout layout, GLenum indexType, GLenum usage);
	~Drawable();

	template<class Vertex, typename IndexType>
	void Submit(const DrawableData<Vertex, IndexType> &data)
	{
		m_VertexBuffer->SetData(data.vertices.data(), SizeOfVector(data.vertices));
		m_IndexBuffer->SetData(data.indices.data(), SizeOfVector(data.indices));

		m_IsSubmitted = true;
	}

	void Generate(Layout layout, GLenum indexType, GLenum usage);
	void Destroy();

	Ref<VertexArray> m_VertexArray;
	Ref<VertexBuffer> m_VertexBuffer;
	Ref<IndexBuffer> m_IndexBuffer;

	Layout m_Layout;

	Ref<Transform> m_Transform;
	RenderRequest m_RenderRequest;

	bool m_IsSubmitted;
};

#endif //MINECRAFT_DRAWABLE_H
