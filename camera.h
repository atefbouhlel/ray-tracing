#ifndef CAMERA_H
#define CAMERA_H
#include "vector3f.h"
namespace app {
	class Camera
	{
	public:
		Camera();
		Camera(Vector3f position, Vector3f direction);
		Camera(Vector3f , Vector3f , Vector3f , Vector3f );

	private:
		Vector3f position_;
		Vector3f direction_;
		Vector3f camright_;
		Vector3f camdown_;

	public:
		/**
		* @return Vector3f : the position of the camera
		*/
		Vector3f getPosition() const { return position_; }
		/**
		* @return Vector3f : the direction of the camera
		*/
		Vector3f getDirection() const { return direction_; }
		/**
		* @return Vector3f : the right direction of the camera
		*/
		Vector3f getRight() const{ return camright_; }
		/**
		* @return Vector3f : the down direction  of the camera
		*/
		Vector3f getDown() const { return camdown_; }

	};

	
}
#endif 

