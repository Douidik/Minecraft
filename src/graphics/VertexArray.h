#ifndef MINECRAFT_VERTEXARRAY_H
#define MINECRAFT_VERTEXARRAY_H

class IndexBuffer;
class VertexBuffer;

class VertexArray
{
public:
	static Ref<VertexArray> Create();

	VertexArray();
	~VertexArray();

	void Bind() const;
	void UnBind() const;

	void AddIndexBuffer(Ref<IndexBuffer> indexBuffer);
	void AddVertexBuffer(Ref<VertexBuffer> vertexBuffer);

	inline Ref<IndexBuffer> GetIndexBuffer()
	{
		return m_IndexBuffer;
	}

	inline std::vector<Ref<VertexBuffer>> GetVertexBuffers()
	{
		return m_VertexBuffers;
	}

//private:
	Ref<IndexBuffer> m_IndexBuffer;
	std::vector<Ref<VertexBuffer>> m_VertexBuffers;

	size_t m_StrideOffset;
	GLuint m_RendererID;
};

#endif //MINECRAFT_VERTEXARRAY_H
