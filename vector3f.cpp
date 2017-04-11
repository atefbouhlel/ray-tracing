#include "vector3f.h"

namespace app {

	Vector3f::Vector3f() {
		x_ = 0;
		y_ = 0;
		z_ = 0;
	}

	Vector3f::Vector3f(float n) : x_(n), y_(n), z_(n) {}

	Vector3f::Vector3f(float x, float y, float z) {
		x_ = x;
		y_ = y;
		z_ = z;
	}

	Vector3f operator * (const Vector3f &v, float val) {
		return Vector3f(v.getX()*val, v.getY()*val, v.getZ()*val);
	}

	Vector3f operator * (float val , const Vector3f &v) {
		return Vector3f(v.getX()*val, v.getY()*val, v.getZ()*val);
	}

	std::ostream & operator<<(std::ostream & std,const Vector3f & v)
	{
		return std << "x= " << v.getX() << ", y: " << v.getY() << ", z: " << v.getZ() ;

	}
}