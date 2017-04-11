#ifndef SCENE_H
#define SCENE_H

#ifdef _WIN32
#  define _CRT_SECURE_NO_DEPRECATE
#endif

#include "shape.h"
#include "camera.h"
#include"light.h"
#include <fstream>
#include <vector>

using namespace std;

namespace app {
	class Scene
	{
	public:
		Scene(Camera c, vector<Shape*> shapes, Light source);
		~Scene();		

	private:
		Camera camera_;
		vector<Shape*> shapes_;
		Light source_;

	public:
		Camera getCamera() const{ return camera_; }
		vector<Shape*> getShapes() const { return shapes_; }
		Light getRay() const { return source_; }

	private:
		/**
		* @param filename char* (string)
		* @param width int
		* @param height int
		* @param data Material* a table that contains the color of the pixels
		* @return \e void but saves a png file
		*/
		void saveImage(const char* filename, int w, int h, Material* data);
		/**
		* @brief Get the color of the intersection
		* @param intersection_position Vector3f
		* @param intersecting_ray_direction Vector3f
		* @param index_of_winning_object int
		* @param accuracy double
		* @return \e Material 
		*/
		Material getColorAt(Vector3f intersection_position, Vector3f intersecting_ray_direction, int index_of_winning_object, double accuracy);
		/**
		* @param object_intersections vector<double>
		* @return \e int the index of the winning intersection
		*/
		int winningObjectIndex(vector<double> object_intersections);
	public:
		/**
		* @brief Render the scene
		* @param filename char* (string)
		* @param width int
		* @param height int
		* @return \e void
		*/
		void render(int, int, char*);



	};
}

#endif 

