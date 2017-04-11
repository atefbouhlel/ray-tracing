#ifdef _WIN32
#  define _CRT_SECURE_NO_DEPRECATE
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <cstdio>
#include <ctime>

#include "cubequad.h"
#include "sphere.h"
#include "scene.h"
#include "light.h"

using namespace std;
using namespace app;

/** 
* @file main.cpp
* @author Sarra Zammit Chatti
* @author Atef Bouhlel
* @brief This file contains the main() function
*/


int main() {

	std::cout << "En cours..." << std::endl;

	Vector3f O(0, 0, 0);
	Vector3f Y(0, 1, 0);
	/** Define the scene's components:
	* Camera
	* Define Camera position
	*/
	Vector3f campos(3, 1.5, -4);
	//! Define Camera directions
	Vector3f look_at(0, 0, 0);
	Vector3f diff_btw(campos.getX() - look_at.getX(), campos.getY() - look_at.getY(), campos.getZ() - look_at.getZ());
	Vector3f camdir = (-diff_btw).normalize();
	Vector3f camright = Y.crossProduct(camdir).normalize();
	Vector3f camdown = camright.crossProduct(camdir);
	Camera scene_cam(campos, camdir, camright, camdown);
	
	//! Light
	Material white_light(1.0, 1.0, 1.0, 0.0);
	//Vector3f light_position(300, 100, -10);
	Vector3f light_position(100, 200, 1);
	Light scene_light(light_position, white_light);


	//Colors
	Material green(0.5, 1.0, 0.5, 0.3);
	Material gray(0.5, 0.5, 0.5, 0.0);
	Material purple(0.6, 0.6, 0.9, 0.2);

	//! Scene's objects
	Sphere scene_sphere(green,O,1);
	Sphere scene_sphere2(purple, Vector3f(-3.0, 1.0, 0.0),1);
	Sphere scene_sphere3(gray, Vector3f(1.5, 0.0, 2.0),1);

	vector<Shape*> scene_objects;
	scene_objects.push_back(dynamic_cast<Shape*>(&scene_sphere));
	scene_objects.push_back(dynamic_cast<Shape*>(&scene_sphere2));
	scene_objects.push_back(dynamic_cast<Shape*>(&scene_sphere3));
	
	/* Scence
	* Scene's dimensions
	*/
	int width = 640;
	int height = 480;
	Scene scene(scene_cam, scene_objects, scene_light);
	//! Rendering the image
	scene.render(width, height, "scene_result.png");
	
	cout << "Fini" << endl;
	scene_objects.clear();
	
}