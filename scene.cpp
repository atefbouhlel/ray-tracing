#include "scene.h"
#include <algorithm>

namespace app {
	Scene::Scene(Camera c, vector<Shape*> shapes, Light source) {
		camera_ = c;
		shapes_ = shapes;
		source_ = source;
	}

	Scene::~Scene()
	{
		shapes_.clear();
	}

	Material Scene::getColorAt(Vector3f intersection_position,
		Vector3f intersecting_ray_direction,
		int index_of_winning_object,
		double accuracy) {
		double ambientlight = 0.2;
		Material winning_object_color = shapes_.at(index_of_winning_object)->getMaterial();
		Vector3f winning_object_normal = shapes_.at(index_of_winning_object)->getNormalAt(intersection_position);

		Material final_color = winning_object_color.colorScalar(ambientlight);

		Vector3f light_direction = (source_.getPosition() + (-intersection_position)).normalize(); 

		float cosine_angle = winning_object_normal.dot(light_direction);

		if (cosine_angle > 0) {
			// test for shadows
			bool shadowed = false;

			Vector3f distance_to_light = (source_.getPosition()+ (-intersection_position)).normalize();
			float distance_to_light_magnitude = distance_to_light.length2();

			Ray3f shadow_ray(intersection_position, (source_.getPosition() + (-intersection_position)).normalize());

			vector<double> secondary_intersections;

			for (int object_index = 0; object_index < shapes_.size() && shadowed == false; object_index++) {
				secondary_intersections.push_back(shapes_.at(object_index)->findIntersection(shadow_ray));
			}

			for (int c = 0; c < secondary_intersections.size(); c++) {
				if (secondary_intersections.at(c) > accuracy) {
					if (secondary_intersections.at(c) <= distance_to_light_magnitude) {
						shadowed = true;
					}
				}
				break;
			}

			if (shadowed == false) {
				final_color = final_color.colorAdd(winning_object_color.colorMultiply(source_.getMaterial()).colorScalar(cosine_angle));

				if (winning_object_color.getShininess() > 0 && winning_object_color.getShininess() <= 1) {
					double dot1 = winning_object_normal.dot(-intersecting_ray_direction);
					Vector3f scalar1 = winning_object_normal * dot1;
					Vector3f add1 = scalar1 + intersecting_ray_direction;
					Vector3f scalar2 = add1* 2;
					Vector3f add2 = (-intersecting_ray_direction) + scalar2;
					Vector3f reflection_direction = add2.normalize();

					double specular = reflection_direction.dot(light_direction);
					if (specular > 0) {
						specular = pow(specular, 10);
						final_color = final_color.colorAdd(source_.getMaterial().colorScalar(specular*winning_object_color.getShininess()));
					}
				}

			}

		}

		return final_color.clip();
	}

	int Scene::winningObjectIndex(vector<double> object_intersections) {		
		int index_of_minimum_value;

		// prevent unnessary calculations
		if (object_intersections.size() == 0) {
			// if there are no intersections
			return -1;
		}
		else if (object_intersections.size() == 1) {
			if (object_intersections.at(0) > 0) {
				// if that intersection is greater than zero then its our index of minimum value
				return 0;
			}
			else {
				// otherwise the only intersection value is negative
				return -1;
			}
		}
		else {
			// otherwise there is more than one intersection
			// first find the maximum value

			double max = 0;
			for (int i = 0; i < object_intersections.size(); i++) {
				if (max < object_intersections.at(i)) {
					max = object_intersections.at(i);
				}
			}

			// then starting from the maximum value find the minimum positive value
			if (max > 0) {
				// we only want positive intersections
				for (int index = 0; index < object_intersections.size(); index++) {
					if (object_intersections.at(index) > 0 && object_intersections.at(index) <= max) {
						max = object_intersections.at(index);
						index_of_minimum_value = index;
					}
				}

				return index_of_minimum_value;
			}
			else {
				// all the intersections were negative
				return -1;
			}
		}
	}


	void Scene::saveImage(const char* filename, int w, int h, Material* data) {
		FILE* file;
		int totalSize = w * h;
		int stride = 4 * totalSize;
		int fileSize = 54 + stride;
		int dpi = 72;

		double factor = 39.375;
		int meter = static_cast<int>(factor);
		int pixelsPerMeter = dpi * meter;

		unsigned char bmpFileHeader[14] = { 'B', 'M', 0,0,0,0, 0,0,0,0, static_cast<char>(54),0,0,0 };
		unsigned char bmpInfoHeader[40];

		// Initialize the table
		std::memset(bmpInfoHeader, 0, sizeof(bmpInfoHeader));

		bmpInfoHeader[0] = static_cast<char>(40);
		bmpInfoHeader[12] = 1;
		bmpInfoHeader[14] = 24;

		bmpFileHeader[2] = (unsigned char)(fileSize);
		bmpFileHeader[3] = (unsigned char)(fileSize >> 8);
		bmpFileHeader[4] = (unsigned char)(fileSize >> 16);
		bmpFileHeader[5] = (unsigned char)(fileSize >> 24);

		bmpInfoHeader[4] = (unsigned char)(w);
		bmpInfoHeader[5] = (unsigned char)(w >> 8);
		bmpInfoHeader[6] = (unsigned char)(w >> 16);
		bmpInfoHeader[7] = (unsigned char)(w >> 24);

		bmpInfoHeader[8] = (unsigned char)(h);
		bmpInfoHeader[9] = (unsigned char)(h >> 8);
		bmpInfoHeader[10] = (unsigned char)(h >> 16);
		bmpInfoHeader[11] = (unsigned char)(h >> 24);

		//Pixels per meter Density
		bmpInfoHeader[21] = (unsigned char)(pixelsPerMeter);
		bmpInfoHeader[22] = (unsigned char)(pixelsPerMeter >> 8);
		bmpInfoHeader[23] = (unsigned char)(pixelsPerMeter >> 16);
		bmpInfoHeader[24] = (unsigned char)(pixelsPerMeter >> 24);

		bmpInfoHeader[25] = (unsigned char)(pixelsPerMeter);
		bmpInfoHeader[26] = (unsigned char)(pixelsPerMeter >> 8);
		bmpInfoHeader[27] = (unsigned char)(pixelsPerMeter >> 16);
		bmpInfoHeader[28] = (unsigned char)(pixelsPerMeter >> 24);

		bmpInfoHeader[29] = (unsigned char)(pixelsPerMeter);
		bmpInfoHeader[30] = (unsigned char)(pixelsPerMeter >> 8);
		bmpInfoHeader[31] = (unsigned char)(pixelsPerMeter >> 16);
		bmpInfoHeader[32] = (unsigned char)(pixelsPerMeter >> 24);

		file = std::fopen(filename, "wb");

		std::fwrite(bmpFileHeader, 1, 14, file);
		std::fwrite(bmpInfoHeader, 1, 40, file);

		for (int i = 0; i<totalSize; i++) {

			double red = (data[i].getRed()) * 255;
			double green = (data[i].getGreen()) * 255;
			double blue = (data[i].getBlue()) * 255;

			unsigned char color[3] = {
				static_cast<unsigned char>((int)std::floor(blue)),
				static_cast<unsigned char>((int)std::floor(green)),
				static_cast<unsigned char>((int)std::floor(red))
			};

			std::fwrite(color, 1, 3, file);
		}

		std::fclose(file);
	}

	void Scene::render(int width, int height, char * filename)
	{
		int thisone;
		double aspectratio = (double)width / (double)height;
		int total = width * height;
		Material* pixels = new Material[total];
		
		double accuracy = 0.00000001;
		/* The purpose of daclaring the accuarcy variable is whenever we have a ray intersects with something
		* we intercept the ray with the sphere if the intersection value is slightly towards
		* the inside of the sphere because of an error in computer then we would have a problem getting
		* the color so we had that value to ensure that the intersection value was only on the outside
		* of the sphere
		*/
		double xamnt, yamnt;

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				thisone = x + y * width;
				if (width > height) {
					// the image is wider than it is tall
					xamnt = ((x + 0.5) / width)*aspectratio - (((width - height) / (double)height) / 2);
					yamnt = ((height - y) + 0.5) / height;
				}
				else if (height > width) {
					// the imager is taller than it is wide
					xamnt = (x + 0.5) / width;
					yamnt = (((height - y) + 0.5) / height) / aspectratio - (((height - width) / (double)width) / 2);
				}
				else {
					// the image is square
					xamnt = (x + 0.5) / width;
					yamnt = ((height - y) + 0.5) / height;
				}

				Vector3f cam_ray_origin = camera_.getPosition();
				Vector3f cam_ray_direction = (camera_.getDirection() + ((camera_.getRight() * (xamnt - 0.5)) + (camera_.getDown() * (yamnt - 0.5)))).normalize();

				Ray3f cam_ray(cam_ray_origin, cam_ray_direction);

				vector<double> intersections;

				for (int index = 0; index < shapes_.size(); index++) {
					intersections.push_back(shapes_.at(index)->findIntersection(cam_ray));
				}

				// determine which object is closer to the camera
				// return -1 or 0 or 1
				//The ray in this pixel either misses everything in the scene 
				// or intersects with the first object in the scene
				// or it can intersect with the second object in the scene
				int index_of_winning_object = winningObjectIndex(intersections);

				if (index_of_winning_object == -1) {
					pixels[thisone].setRed(0);
					pixels[thisone].setGreen(0);
					pixels[thisone].setBlue(0);
				}
				else
				{
					/* Get the color at the specific XYZ coordinates of the intersection so instead of
					getting the color of the object and setting that color in the pixel  we are going to
					have to actually get the color of the intersection*/
					if (intersections.at(index_of_winning_object) > accuracy) {
						Material this_color = shapes_.at(index_of_winning_object)->getMaterial();
						// determine the position and direction vectors at the point of intersection

						Vector3f intersection_position = cam_ray_origin + (cam_ray_direction * (intersections.at(index_of_winning_object)));
						Vector3f intersecting_ray_direction = cam_ray_direction;

						Material intersection_color = getColorAt(intersection_position, intersecting_ray_direction, index_of_winning_object, accuracy);
						//Material intersection_color = scene_objects.at(index_of_winning_object)->getMaterial();

						pixels[thisone].setRed(intersection_color.getRed()); //.r_ = intersection_color.getRed();
						pixels[thisone].setGreen(intersection_color.getGreen());// .g = intersection_color.getGreen();
						pixels[thisone].setBlue(intersection_color.getBlue());//.b = intersection_color.getBlue();
					}
				}

			}
		}

		saveImage(filename, width, height, pixels);
	}

}