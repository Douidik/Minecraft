
#include "Maths.h"

Ref<Transform> Transform::Create(Vector3 _position, Vector3 _rotation, Vector3 _scale)
{
	return CreateRef<Transform>(_position, _rotation, _scale);
}


Transform::Transform(Vector3 _position, Vector3 _rotation, Vector3 _scale)
	: position(_position), rotation(_rotation), scale(_scale)
{ }

Ref<Matrix4> Transform::CreateMatrix() const
{
	Ref<Matrix4> matrix = CreateRef<Matrix4>(1.0f);

	*matrix = glm::scale(*matrix, scale);

	*matrix = glm::rotate(*matrix, glm::radians(rotation.x), {1,0,0});
	*matrix = glm::rotate(*matrix, glm::radians(rotation.y), {0,1,0});
	*matrix = glm::rotate(*matrix, glm::radians(rotation.z), {0,0,1});

	*matrix = glm::translate(*matrix, position);

	return matrix;
}