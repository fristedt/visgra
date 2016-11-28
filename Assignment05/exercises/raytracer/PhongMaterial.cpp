#include "PhongMaterial.hpp"
#include "Light.hpp"
#include "Math.hpp"
#include "Ray.hpp"

namespace rt
{

  PhongMaterial::PhongMaterial(const Vec3d& color, double reflectance, double shininess) :  
    Material(color,reflectance), mShininess(shininess)
  {

  }

  Vec4d PhongMaterial::shade(const RayIntersection& intersection,
    const Light& light) const 
  {
	  // get normal and light direction
	  Vec3d N = intersection.normal();
	  Vec3d L = (light.position() - intersection.position()).normalize();

	  double cosNL = std::max(dot(N, L), double(0));

	  // Programming Task 2: Extend this method.
	  // This method currently implements a Lambert's material with ideal
	  // diffuse reflection.
	  // Your task is to implement a Phong shading model.
	  
    // Hints:
    //
    // 1. This function should return the sum of diffuse and specular parts as
    //    mentioned in slide 59 of Lecture 6. 
    
    // 2. The incident radiance from the light source is the light intensity divided by
    //    the quadratic distance of the light source from the point of intersection. (quadratic falloff)
    //
    // 3. The irradiance c_l is obtained by multiplying the incident radiance 
    //    to the cosine of the angle between the vectors L and N.
    //
    // 4. The view vector V is the direction of the ray which intersects the object.
    //
    // 5. The reflection vector R can be obtained by using the predefined function reflect (raytracer/Vector3.hpp)
    //
    // 6. The rest of the terms as per the slides are as follows (including normalization)
    //    c_r = material_color / PI
    //    p = mShininess
    //    c_p = r_f0 * (mShininess + 2) / (2 * PI)
    //
	  return Vec4d(this->color()*cosNL, 1.0);
  }

} //namespace rt
