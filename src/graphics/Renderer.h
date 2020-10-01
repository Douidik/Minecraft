#ifndef MINECRAFT_RENDERER_H
#define MINECRAFT_RENDERER_H

#include "maths/Maths.h"

class VertexArray;
class ShaderProgram;
class Camera;

struct RenderRequest
{
	RenderRequest() = default;

	RenderRequest(Ref<VertexArray> _vertexArray, Ref<Transform> _transformation)
		: vertexArray(_vertexArray), transformation(_transformation)
	{}

	Ref<VertexArray> vertexArray;
	Ref<Transform> transformation;
};

class Renderer
{
public:
	static void Initialize();
	static void Clear();

	static Ref<Renderer> Create();
	Renderer();
	void Update();
	void Draw(RenderRequest request);

	Ref<ShaderProgram> GetShader() const
	{
		return m_ShaderProgram;
	}

	inline void SetMainCamera(Ref<Camera> mainCamera)
	{
		m_MainCamera = mainCamera;
	}

private:
	// Loading default shader program
	virtual void LoadShader();

	Ref<Matrix4> m_ViewProjectionMatrix;
	Ref<Camera> m_MainCamera;
	Ref<ShaderProgram> m_ShaderProgram;

	static bool s_IsInitialized;
};

#endif //MINECRAFT_RENDERER_H
