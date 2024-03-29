#ifndef PHONGMATERIAL_HPP_INCLUDE_ONCE
#define PHONGMATERIAL_HPP_INCLUDE_ONCE

#include "raytracerConfig.hpp"

#include "Material.hpp"

namespace rt
{

  class RayIntersection;
  class Light;

  /// Material based on Lambert's cosine law
  /// see http://en.wikipedia.org/wiki/Lambert%27s_cosine_law
  class PhongMaterial : public Material
  {
  public:
    RAYTRACER_EXPORTS PhongMaterial(const Vec3d& color = Vec3d(0,0.4,0.8),
      double reflectance=1.0,
      double shininess=10.0);

    RAYTRACER_EXPORTS Vec4d shade(const RayIntersection& intersection, 
      const Light& light) const override;

  private:

    double mShininess; 
  };

} //namespace rt

#endif // PHONGMATERIAL_HPP_INCLUDE_ONCE
