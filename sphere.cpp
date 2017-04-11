#include "sphere.h"
namespace app {
	/**
	* \file      sphere.h
	* \author    Miroslav
	* \version   1.0
	* \date       12 Novembre 2009
	* \brief       Définit les modèles de voiture et leur particularités.
	*
	* \details    Cette classe surcharge les accesseurs standards du module_voiture pour
	*                  convenir aux spécificités des différents modèles possibles.
	*/
	Sphere::Sphere() {
		matter_ = Material();
		origin_ = Vector3f(0);
		radius_ = 1;
	}
	Sphere::Sphere(Material m, Vector3f origin, float radius) {
		matter_ = m;
		origin_ = origin;
		radius_ = radius;
	}

	double Sphere::findIntersection(Ray3f ray) {
		Vector3f ray_origin = ray.getOrigin();
		double ray_origin_x = ray_origin.getX();
		double ray_origin_y = ray_origin.getY();
		double ray_origin_z = ray_origin.getZ();

		Vector3f ray_direction = ray.getDirection();
		double ray_direction_x = ray_direction.getX();
		double ray_direction_y = ray_direction.getY();
		double ray_direction_z = ray_direction.getZ();

		Vector3f sphere_center = origin_;
		double sphere_center_x = sphere_center.getX();
		double sphere_center_y = sphere_center.getY();
		double sphere_center_z = sphere_center.getZ();

		double a = 1; // normalized
		double b = (2 * (ray_origin_x - sphere_center_x)*ray_direction_x) + (2 * (ray_origin_y - sphere_center_y)*ray_direction_y) + (2 * (ray_origin_z - sphere_center_z)*ray_direction_z);
		double c = pow(ray_origin_x - sphere_center_x, 2) + pow(ray_origin_y - sphere_center_y, 2) + pow(ray_origin_z - sphere_center_z, 2) - (radius_*radius_);

		double discriminant = b*b - 4 * c;

		if (discriminant > 0) {
			/// the ray intersects the sphere

			// the first root
			double root_1 = ((-1 * b - sqrt(discriminant)) / 2) - 0.000001;

			if (root_1 > 0) {
				// the first root is the smallest positive root
				return root_1;
			}
			else {
				// the second root is the smallest positive root
				double root_2 = ((sqrt(discriminant) - b) / 2) - 0.000001;
				return root_2;
			}
		}
		else {
			// the ray missed the sphere
			return -1;
		}
	}


	std::ostream & operator<<(std::ostream & std,const Sphere & sphere)
	{
		return std << " Materiel: " << sphere.getMaterial() << "\n Origin: " << sphere.getOrigin() << "\n Radius: " << sphere.getRadius() << "\n";
	}
}