#ifndef MINECRAFT_UTILITY_H
#define MINECRAFT_UTILITY_H

#define SIZEOF_CONTAINER(container) container.empty() ? 0 : (container.size() * sizeof(container[0]))

template<typename T>
size_t SizeOfVector(const typename std::vector<T> &vector)
{
	return sizeof(T) * vector.size();
}

template<typename T, size_t N>
size_t ArrayCount(const T (&array)[N])
{
	return N;
}

static size_t SizeOfGLType(GLenum type)
{
	switch (type)
	{
	case GL_BYTE:
		return sizeof(char);
	case GL_UNSIGNED_BYTE:
		return sizeof(unsigned char);
	case GL_SHORT:
		return sizeof(short);
	case GL_UNSIGNED_SHORT:
		return sizeof(unsigned short);
	case GL_INT:
		return sizeof(int);
	case GL_UNSIGNED_INT:
		return sizeof(unsigned int);
	case GL_FLOAT:
		return sizeof(float);
	case GL_2_BYTES:
		return sizeof(char) * 2;
	case GL_3_BYTES:
		return sizeof(char) * 3;
	case GL_4_BYTES:
		return sizeof(char) * 4;
	case GL_DOUBLE:
		return sizeof(double);
	default:
		MC_ERROR("OpenGL Type {} is not supported", std::to_string(type));
		return 0;
	}
}

#endif //MINECRAFT_UTILITY_H
