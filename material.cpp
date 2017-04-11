#include "material.h"
#include "ray3f.h"

namespace app {
	Material::Material()
	{
		r_ = 0.5; g_ = 0.5; b_ = 0.5; shininess_ = 0;
	}

	Material::Material(float r, float g, float b, float shininess) {
		r_ = r;
		g_ = g;
		b_ = b;
		shininess_ = shininess;
	}

	
	 std::ostream & operator<<(std::ostream & std, const Material & m)
	 {
		 return std <<  "Rouge: " << m.getRed() << ", Bleu: " << m.getBlue() << ", Vert: " << m.getGreen() << ", Coef de reflexion: " << m.getShininess();
		
	 }

}