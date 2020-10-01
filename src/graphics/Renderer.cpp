#include "Renderer.h"
#include "core/Context.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"
#include "core/Configuration.h"
#include "Camera.h"

bool Renderer::s_IsInitialized = false;

void Renderer::Initialize()
{
	MC_ASSERT(Context::IsAvailable(), "No context available for rendering");

	/* Initializing GLEW */
	glewExperimental = true;
	MC_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW");
	s_IsInitialized = true;

	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glEnable(GL_CULL_FACE));
}

Ref<Renderer> Renderer::Create()
{
	return CreateRef<Renderer>();
}

Renderer::Renderer()
{
	/* Prevent from initializing the rendering system twice */
	if(!s_IsInitialized)
		Initialize();

	LoadShader();
	m_ViewProjectionMatrix = CreateRef<Matrix4>(1.0f);
}

void Renderer::LoadShader()
{
	/* Default shader */
	m_ShaderProgram = ShaderProgram::Create("res/shaders/Block.vs", "res/shaders/Block.fs");
}

void Renderer::Update()
{
	if(m_MainCamera != nullptr)
		*m_ViewProjectionMatrix = (*m_MainCamera->CreateProjectionMatrix()) * (*m_MainCamera->CreateViewMatrix());
	else
	{
		MC_LOG_WARN("No main camera bound in renderer");
		*m_ViewProjectionMatrix = Matrix4(1.0f);
	}

	m_ShaderProgram->Bind();
	m_ShaderProgram->SetMatrix4(Configuration::Read<std::string>("UniformName.ViewProjection"), *m_ViewProjectionMatrix);
}


void Renderer::Draw(RenderRequest request)
{
	/* Binding OpenGL Objects */
	m_ShaderProgram->Bind();
	request.vertexArray->Bind();

	/* Sending the model transformation matrix */
	Ref<Matrix4> transformMatrix = request.transformation->CreateMatrix();
	m_ShaderProgram->SetMatrix4(Configuration::Read<std::string>("UniformName.Transform"), *transformMatrix);

	auto indexBuffer = request.vertexArray->GetIndexBuffer();
	GLCall(glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), indexBuffer->GetType(), nullptr));

	request.vertexArray->UnBind();
}

void Renderer::Clear()
{
	glClearColor(0.53, 0.81, 0.92, 0.0);
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}