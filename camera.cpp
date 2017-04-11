#include "camera.h"

namespace app {
	Camera::Camera()
	{
		position_ = Vector3f(0);
		direction_ = Vector3f(0, 0, 1);
		camright_ = Vector3f(0);
		camdown_ = Vector3f(0);
	}

	Camera::Camera(Vector3f position, Vector3f direction)
	{
		position_ = position;
		direction_ = direction;
	}

	Camera::Camera(Vector3f position, Vector3f direction, Vector3f right, Vector3f down)
	{
		position_ = position;
		direction_ = direction;
		camright_ = right;
		camdown_ = down;
	}

}