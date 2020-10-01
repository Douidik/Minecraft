#ifndef MINECRAFT_INDEXBUFFER_H
#define MINECRAFT_INDEXBUFFER_H

#include "Buffer.h"

class IndexBuffer : public Buffer
{
public:
	static Ref<IndexBuffer> Create(const void *data, size_t size, GLenum type, GLenum usage);
	static Ref<IndexBuffer> Create(GLenum type, GLenum usage);

	IndexBuffer(const void *data, size_t size, GLenum type, GLenum usage);
	IndexBuffer(GLenum type, GLenum usage);

	void Bind() override;
	void UnBind() override;

	void SetData(const void *data, size_t size) override;

	inline size_t GetCount() const
	{
		return m_Count;
	}

	inline GLenum GetType() const
	{
		return m_Type;
	}

private:
	size_t m_Count;
	GLenum m_Type;
};

#endif //MINECRAFT_INDEXBUFFER_H
