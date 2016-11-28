#include "PhongMaterial.hpp"
#include "Light.hpp"
#include "Math.hpp"
#include "Ray.hpp"

#define PI 3.1415

namespace rt {

    PhongMaterial::PhongMaterial(const Vec3d& color, double reflectance, double shininess) :
        Material(color, reflectance), mShininess(shininess) {

    }

    Vec4d PhongMaterial::shade(const RayIntersection& intersection,
        const Light& light) const {
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

        double quadDist = (light.position() - intersection.position()).lengthSquared();
        Vec3d incidentRadiance = light.spectralIntensity() / quadDist;

        // 3. The irradiance c_l is obtained by multiplying the incident radiance 
        //    to the cosine of the angle between the vectors L and N.

        Vec3d c_l = incidentRadiance * cosNL;

        // 4. The view vector V is the direction of the ray which intersects the object.

        Vec3d V = intersection.ray().direction();

        // 5. The reflection vector R can be obtained by using the predefined function reflect (raytracer/Vector3.hpp)
        Vec3d R = reflect(L, N);

        // 6. The rest of the terms as per the slides are as follows (including normalization)
        //    c_r = material_color / PI
        //    p = mShininess
        //    c_p = r_f0 * (mShininess + 2) / (2 * PI)

        double specAngle = dot(R, V) > 0 ? dot(R, V) : 0;
        double specular = pow(specAngle, mShininess);
        Vec3d c_r = this->color() / PI;
        Vec3d c_p = Vec3d(1,1,1) * (mShininess + 2) / (2 * PI);
        Vec3d c_diff = c_r * c_l * cosNL;
        Vec3d c_spec = c_p * c_l * specular;

        double p_s = 0.04;
        return Vec4d(c_diff + p_s * c_spec, 1.0);
    }

} //namespace rt
