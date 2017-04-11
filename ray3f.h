#ifndef RAY_H
#define RAY_H
#include "vector3f.h"
namespace app {
	class Ray3f
	{
	public:
		Ray3f();
		Ray3f(Vector3f origin);
		Ray3f(Vector3f origin, Vector3f direction);

	private:
		Vector3f origin_;
		Vector3f direction_;

	public:
		Vector3f getOrigin() const { return origin_; }
		Vector3f getDirection() const { return direction_; }


	};

}

#endif