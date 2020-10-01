#include "Camera.h"
#include "core/Configuration.h"

Ref<Camera> Camera::Create()
{
	return CreateRef<Camera>();
}

Camera::Camera()
{
	m_Transform = Transform::Create();

	/* Retrieve camera configuration */
	m_Configuration.fieldOfView = Configuration::Read<float>("Camera.FieldOfView");
	m_Configuration.zNear = Configuration::Read<float>("Camera.zNear");
	m_Configuration.zFar  = Configuration::Read<float>("Camera.zFar");
}

Ref<Matrix4> Camera::CreateProjectionMatrix()
{
	float aspectRatio = Configuration::Read<float>("Window.Width") / Configuration::Read<float>("Window.Height");

	return CreateRef<Matrix4>(glm::perspective(glm::radians(m_Configuration.fieldOfView),
											   aspectRatio,
											   m_Configuration.zNear,
											   m_Configuration.zFar));
}

Ref<Matrix4> Camera::CreateViewMatrix()
{
	/*
	 * To convert camera world space transformation into a view transformation
	 * we take the world space and invert the position vector
	 */
	Transform viewTransform = *m_Transform;
	viewTransform.position = -viewTransform.position;

	return viewTransform.CreateMatrix();
}
