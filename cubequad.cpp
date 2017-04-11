#include "cubequad.h"

namespace app {
	Cubequad::Cubequad() {
		matter_ = Material();
		origin_ = Vector3f();
		width_ = Vector3f();
		height_ = Vector3f();
	}


	Cubequad::Cubequad(Material m, Vector3f origin, Vector3f width, Vector3f height) {
		matter_ = m;
		origin_ = origin;
		width_ = width;
		height_ = height;
	}
	
	double Cubequad::findIntersection(Ray3f ray) {
		//TODO
		return 1.0;
	}

	std::ostream & operator<<(std::ostream & std, const Cubequad & cq)
	{
		return std << " Materiel: " << cq.getMaterial() << "\n Origin: " << cq.getOrigin() << "\n Width: " << cq.getWidth() << "\n Height: " << cq.getHeight() << "\n";
	}
}