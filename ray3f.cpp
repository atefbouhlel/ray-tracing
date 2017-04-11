#include "ray3f.h"

namespace app {

	Ray3f::Ray3f() {
		origin_ = Vector3f(0);
		direction_ = Vector3f(1,0,0);
	}

	Ray3f::Ray3f(Vector3f origin) {
		origin_ = origin;
	}

	Ray3f::Ray3f(Vector3f origin, Vector3f direction)
	{
		origin_ = origin;
		direction_ = direction;
	}
}