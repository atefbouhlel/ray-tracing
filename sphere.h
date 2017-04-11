#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"
#include <iostream>
namespace app {
	class Sphere : public Shape
	{
	public:
		Sphere();
		Sphere(Material m, Vector3f origin, float radius);

	private:
		Vector3f origin_;
		float radius_;

	public:
		Vector3f getOrigin() const { return origin_; }
		float getRadius() const { return radius_; }

	public:
		virtual Vector3f getNormalAt(Vector3f point) {
			// normal always points away from the center of a sphere
			Vector3f normal_Vect = (point + (-origin_));
			normal_Vect = normal_Vect.normalize();
			return normal_Vect;
		}

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
		* @brief Display the sphere's parameters
		* @param std ostream
		* @param sphere Sphere the sphere to display
		* @return \e ostream
		*/
		friend std::ostream & operator<<(std::ostream &std, const Sphere & sphere);

	};
}

#endif
