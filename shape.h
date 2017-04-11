#ifndef SHAPE_H
#define SHAPE_H

#include "material.h"
#include "ray3f.h"

namespace app {
	class Shape
	{
	protected:
		Material matter_;		

	public:
		virtual Material getMaterial() const{ return matter_; }

	public:
		virtual Vector3f getNormalAt(Vector3f intersection_position) {
			return Vector3f(0);
		}

		/**
		* @brief Find the intersection between an object and a ray
		* @details if the ray intersects an object in the scene, it will not be infinite in that direction
		* it's going to stop and terminate at the intersection point
		* @param ray Ray3f
		* @return \e double the distance from our ray origin to the point of intersection
		*/
		virtual double findIntersection(Ray3f ray) = 0; 

	};
}

#endif