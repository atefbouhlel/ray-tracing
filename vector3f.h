#ifndef VECTOR3F_H
#define VECTOR3F_H
#include <iostream>
namespace app {
	class Vector3f
	{
	public:
		Vector3f();
		Vector3f(float n);
		Vector3f(float x, float y, float z);

	private:
		float x_;
		float y_;
		float z_;

	public:
		/**
		* @return \e float : the vector's x coordinate
		*/
		float getX() const { return x_; }
		/**
		* @return \e float : the vector's y coordinate
		*/
		float getY() const { return y_; }
		/**
		* @return \e float : the vector's z coordinate
		*/
		float getZ() const { return z_; }

	public:
		/**
		* @param x the value to set
		* @return \e void
		*/
		void setX(float x) { x_ = x ; }
		/**
		* @param y the value to set
		* @return \e void
		*/
		void setY(float y) { y_ = y; }
		/**
		* @param z the value to set
		* @return \e void
		*/
		void setZ(float z) { z_ = z; }

	public:
		/**
		* @brief Calculate the vector's length square
		* @return \e float 
		*/
		float length2() const { return x_ * x_ + y_ * y_ + z_ * z_; }
		/**
		* @brief Calculate the vector's length or magnitude
		* @return \e float
		*/
		float length() const { return sqrt(length2()); }

		/**
		* @brief Normalize a vector
		* @return \e Vector3f 
		*/
		Vector3f normalize() {
			return Vector3f(x_ / length(), y_ / length(), z_ / length());
		}

		/**
		* @brief Compute the scalar product of two vectors
		* @param v the second vector 
		* @return \e float
		*/
		float dot(const Vector3f &v) const { return x_ * v.getX() + y_ * v.getY() + z_ * v.getZ(); }

		/**
		* @brief Compute the cross product of two vectors
		* @param v the second vector
		* @return \e Vector3f
		*/
		Vector3f crossProduct(Vector3f v) {
			return Vector3f(y_*v.getZ() - z_*v.getY(), z_*v.getX() - x_*v.getZ(), x_*v.getY() - y_*v.getX());
		}


		/*friend Vector3f operator - (const Vector3f &v1 , const Vector3f &v2) {
			return Vector3f(v1.x_-v2.getX(), v1.y_ - v2.y_, v1.z_ - v2.z_); 
		}*/

		/**
		* @brief Sum two vectors
		* @param v the second vector to add to the current vector
		* @return \e Vector3f
		*/
		Vector3f operator + (const Vector3f &v) const { return Vector3f(x_ + v.x_, y_ + v.y_, z_ + v.z_); }
		/**
		* @brief Subtract two vectors
		* @param v Vector3f the second vector 
		* @return \e Vector3f
		*/
		Vector3f operator - (const Vector3f &v) const { return Vector3f(x_ - v.x_, y_ - v.y_, z_ - v.z_); }
		/**
		* @brief Multiply the vector by -1
		* @return \e Vector3f
		*/
		Vector3f operator - () const { return Vector3f(-x_, -y_, -z_); }
		/**
		* @brief Multiply two vectors
		* @param v Vector3f the second vector
		* @return \e Vector3f
		*/
		Vector3f operator * (const Vector3f &v) const { return Vector3f(x_ * v.x_, y_ * v.y_, z_ * v.z_); }
		/**
		* @brief Multiply a vector by a float value
		* @param v Vector3f 
		* @param val \e float
		* @return \e Vector3f
		*/
		friend Vector3f operator * (const Vector3f &v, float val);

		/**
		* @brief Multiply a value to the vector
		* @param val \e float
		* @param v Vector3f 		
		* @return \e Vector3f
		*/
		friend Vector3f operator * (float val, const Vector3f &v);

		/**
		* @brief Display the vector's parameters 
		* @param std ostream
		* @param v Vector3f the victor to display
		* @return \e ostream
		*/
		friend std::ostream & operator<<(std::ostream & std, const Vector3f & v);

	};
}

#endif
