#ifndef MINECRAFT_GLDEBUG_H
#define MINECRAFT_GLDEBUG_H

	inline void GLClearError()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	bool GLCheckError();

#if defined(MC_DEBUG)
#if defined(MC_LOG_OPENGL_COMMANDS)
	#define GLCall(x) GLClearError();  \
	                  x;               \
	                  MC_LOG_DEBUG(#x);\
	                  GLCheckError()
#else
	#define GLCall(x) GLClearError();  \
	                  x;               \
	                  GLCheckError()
#endif

#else
	#define GLCall(x) x
#endif

#endif //MINECRAFT_GLDEBUG_H
