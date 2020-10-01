#ifndef MINECRAFT_SHADERPROGRAM_H
#define MINECRAFT_SHADERPROGRAM_H

#include "maths/Maths.h"

class ShaderProgram
{
public:
	static Ref<ShaderProgram> Create(const fs::path &vertexPath, const fs::path &fragmentPath);

	ShaderProgram(const fs::path &vertexPath, const fs::path &fragmentPath);
	~ShaderProgram();

	void Bind() const;
	void UnBind() const;

	/* Uniforms */
	void SetUnsigned(const std::string &name, unsigned int &value);
	void SetInteger(const std::string &name, int value);
	void SetFloat(const std::string &name, float value);

	void SetVector2(const std::string &name, Vector2 value);
	void SetVector3(const std::string &name, Vector3 value);
	void SetVector4(const std::string &name, Vector4 value);

	void SetMatrix3(const std::string &name, Matrix3 &value, bool transpose = false);
	void SetMatrix4(const std::string &name, Matrix4 &value, bool transpose = false);

private:
	std::pair<const std::string, const std::string> ReadShaders(const fs::path &vertexPath, const fs::path &fragmentPath);
	GLuint CreateProgram(std::pair<const std::string, const std::string> sources);
	GLuint CreateShader(const std::string &source, GLenum type);

	int GetUniformLocation(const std::string &name);

	GLuint m_RendererID;
	std::unordered_map<std::string, int> m_UniformCache;
};

#endif //MINECRAFT_SHADERPROGRAM_H
