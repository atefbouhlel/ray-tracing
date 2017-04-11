#ifndef CUBEQUAD_H
#define CUBEQUAD_H

#include "shape.h"
namespace app {
	class Cubequad : public Shape
	{
	public:
		Cubequad();
		Cubequad(Material m, Vector3f origin, Vector3f width, Vector3f height);

	private:
		Vector3f origin_;
		Vector3f width_;
		Vector3f height_;
		

	public:
		Vector3f getOrigin() const { return origin_; }
		Vector3f getWidth() const { return width_; }
		Vector3f getHeight() const { return height_; }

	public:
		/**
		* @brief Find the intersection between an object and a ray
		* @details if the ray intersects an object in the scene, it will not be infinite in that direction
		* it's going to stop and terminate at the intersection point
		* @param ray Ray3f
		* @return \e double the distance from our ray origin to the point of intersection
		*/
		virtual double findIntersection(Ray3f ray);

	public:
		/**
		* @brief Display the Cubequad's parameters
		* @param std ostream
		* @param cq Cubequad the cubequad to display
		* @return \e ostream
		*/
		friend std::ostream & operator<<(std::ostream & std, const Cubequad & cq);
	};
}

#endif
