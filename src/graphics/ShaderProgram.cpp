
#include "ShaderProgram.h"

Ref<ShaderProgram> ShaderProgram::Create(const fs::path &vertexPath, const fs::path &fragmentPath)
{
	return CreateRef<ShaderProgram>(vertexPath, fragmentPath);
}

ShaderProgram::~ShaderProgram()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void ShaderProgram::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void ShaderProgram::UnBind() const
{
	GLCall(glUseProgram(0));
}

ShaderProgram::ShaderProgram(const fs::path &vertexPath, const fs::path &fragmentPath)
{
	auto sources = ReadShaders(vertexPath, fragmentPath);
	m_RendererID = CreateProgram(sources);
}

std::pair<const std::string, const std::string> ShaderProgram::ReadShaders(const fs::path &vertexPath, const fs::path &fragmentPath)
{
	/* Asserting both sources are valid */
	MC_ASSERT(fs::exists(vertexPath), "Failed to read shader from: {}" + vertexPath.string());
	MC_ASSERT(fs::exists(fragmentPath), "Failed to read shader from: {}" + fragmentPath.string());

	std::ifstream vertexIfs(vertexPath), fragmentIfs(fragmentPath);
	std::stringstream vertexSstr, fragmentSstr;

	/* Reading the sources from stream */
	vertexSstr 	 << vertexIfs.rdbuf();
	fragmentSstr << fragmentIfs.rdbuf();

	/* Converting the sources to string */
	return { vertexSstr.str(), fragmentSstr.str() };
}

GLuint ShaderProgram::CreateProgram(std::pair<const std::string, const std::string> sources)
{
	/* Creating the shaders from sources */
	GLuint vertexID   = CreateShader(sources.first, GL_VERTEX_SHADER);
	GLuint fragmentID = CreateShader(sources.second, GL_FRAGMENT_SHADER);

	/* Creating the program from shaders */
	GLuint id = glCreateProgram();

	GLCall(glAttachShader(id, vertexID));
	GLCall(glAttachShader(id, fragmentID));

	GLCall(glLinkProgram(id));

	GLint linkResult;
	GLCall(glGetProgramiv(id, GL_LINK_STATUS, &linkResult));

	if(linkResult != GL_TRUE) // Program linkage failed ?
	{
		GLchar glLog[2048]; // Creating the buffer for the error, max length is 2048
		GLCall(glGetProgramInfoLog(id, 2048, nullptr, &glLog[0]));

		// Converting the log for our string format
		std::string log(glLog);
		MC_LOG_ERROR(log);
	}

	/* Detaching and deleting shaders */
	GLCall(glDetachShader(id, vertexID));
	GLCall(glDetachShader(id, fragmentID));

	GLCall(glDeleteShader(vertexID));
	GLCall(glDeleteShader(fragmentID));

	return id;
}

GLuint ShaderProgram::CreateShader(const std::string &source, GLenum type)
{
	GLuint id = glCreateShader(type);
	// Converting source for OpenGL format
	const GLchar *glSource = source.c_str();
	GLCall(glShaderSource(id, 1, &glSource, nullptr));
	GLCall(glCompileShader(id));
	int compileStatus;
	glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);

	return id;
}

/* Uniform */

void ShaderProgram::SetUnsigned(const std::string &name, unsigned int &value)
{
	GLCall(glUniform1ui(GetUniformLocation(name), value));
}
void ShaderProgram::SetInteger(const std::string &name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}
void ShaderProgram::SetFloat(const std::string &name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void ShaderProgram::SetVector2(const std::string &name, Vector2 value)
{
	GLCall(glUniform2f(GetUniformLocation(name), value.x, value.y));
}
void ShaderProgram::SetVector3(const std::string &name, Vector3 value)
{
	GLCall(glUniform3f(GetUniformLocation(name), value.x, value.y, value.z));
}
void ShaderProgram::SetVector4(const std::string &name, Vector4 value)
{
	GLCall(glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w));
}

void ShaderProgram::SetMatrix3(const std::string &name, Matrix3 &value, bool transpose)
{
	GLCall(glUniformMatrix3fv(GetUniformLocation(name), 1, transpose, glm::value_ptr(value)));
}
void ShaderProgram::SetMatrix4(const std::string &name, Matrix4 &value, bool transpose)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, transpose, glm::value_ptr(value)));
}

int ShaderProgram::GetUniformLocation(const std::string &name)
{
	if(m_UniformCache.find(name) != m_UniformCache.end())
	{
		return m_UniformCache[name];
	}

	int location = glGetUniformLocation(m_RendererID, name.c_str());

	if(location == -1) // Uniform Location not found ?
	{
		MC_LOG_WARN("Failed to find uniform location of: {}", name);
	}

	m_UniformCache[name] = location;
	return location;
}
