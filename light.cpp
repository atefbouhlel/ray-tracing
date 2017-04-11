#include "light.h"

namespace app {

	Light::Light()
	{
		position_ = Vector3f(0);
		material_ = Material(1, 1, 1, 0);
	}

	Light::Light(Vector3f p, Material m) {
		position_ = p;
		material_ = m;
	}

}
