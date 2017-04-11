#ifndef MATERIAL_H
#define MATERIAL_H

#include <ostream>

namespace app {
	class Material
	{
	public:
		Material();
		Material(float r, float g, float b, float shininess);

	private:
		float r_, g_,b_, shininess_;

	public:
		float getRed() const { return r_; }
		float getGreen() const { return g_; }
		float getBlue() const { return b_; }
		float getShininess() const { return shininess_; }

		void setRed(double RValue) { r_ = RValue; }
		void setGreen(double GValue) { g_ = GValue; }
		void setBlue(double BValue) { b_ = BValue; }
		void setShinniness(double specialValue) { shininess_ = specialValue; }

	public:
		double brightness() {
			return(r_ + g_ + b_) / 3;
		}

		Material colorScalar(double scalar) {
			return Material(r_*scalar, g_*scalar, b_*scalar, shininess_);
		}

		Material colorAdd(Material color) {
			return Material(r_ + color.getRed(), g_ + color.getGreen(), b_ + color.getBlue(), shininess_);
		}

		Material colorMultiply(Material color) {
			return Material(r_*color.getRed(), g_*color.getGreen(), b_*color.getBlue(), shininess_);
		}

		Material colorAverage(Material color) {
			return Material((r_ + color.getRed()) / 2, (g_ + color.getGreen()) / 2, (b_ + color.getBlue()) / 2, shininess_);
		}

		Material clip() {
			double alllight = r_ + g_ + b_;
			double excesslight = alllight - 3;
			if (excesslight > 0) {
				r_ = r_ + excesslight*(r_ / alllight);
				g_ = g_ + excesslight*(g_ / alllight);
				b_ = b_ + excesslight*(b_ / alllight);
			}
			if (r_ > 1) { r_ = 1; }
			if (g_ > 1) { g_ = 1; }
			if (b_ > 1) { b_ = 1; }
			if (r_ < 0) { r_ = 0; }
			if (g_ < 0) { g_ = 0; }
			if (b_ < 0) { b_ = 0; }

			return Material(r_, g_, b_, shininess_);
		}
		

	public:
		/**
		* @brief Display the material's parameters
		* @param std ostream
		* @param m Material the material to display
		* @return \e ostream
		*/
		friend std::ostream & operator<<(std::ostream &std, const Material & m);
	};

	
}

#endif