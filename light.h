#ifndef LIGHT_H
#define LIGHT_H

#include "vector3f.h"
#include "material.h"

namespace app {
	class Light 
	{

	private:
		Vector3f position_;
		Material material_;

	public:
		Light();
		Light(Vector3f, Material);
		/**
		* @return \e Vector3f : the light's position
		*/
		Vector3f getPosition() { return position_; }
		/**
		* @return \e float : the light's material (color)
		*/
		Material getMaterial() { return material_; }


	};
}
#endif
