#ifndef MINECRAFT_CAMERA_H
#define MINECRAFT_CAMERA_H

#include "maths/Maths.h"

struct CameraConfiguration
{
	float fieldOfView, zNear, zFar;
};

class Camera
{
public:
	static Ref<Camera> Create();
	Camera();
	Ref<Matrix4> CreateProjectionMatrix();
	Ref<Matrix4> CreateViewMatrix();

	/* Replace native transform component */
	inline void SetTransform(Ref<Transform> transform)
	{
		m_Transform = transform;
	}

	inline Ref<Transform> GetTransform()
	{
		return m_Transform;
	}

private:
	Ref<Transform> m_Transform;
	CameraConfiguration m_Configuration;
};

#endif //MINECRAFT_CAMERA_H
