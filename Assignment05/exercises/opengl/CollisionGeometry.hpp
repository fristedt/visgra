#ifndef COLLISIONGEOMETRY_HPP_INCLUDE_ONCE
#define COLLISIONGEOMETRY_HPP_INCLUDE_ONCE
#include "openglConfig.hpp"

#include "OpenGL.hpp"
#include "BVTree.hpp"
#include <vector>
#include <memory>

namespace ogl
{

  // This class uploads and stores an indexed triangle mesh on the GPU
  // It also stores a uniform buffer object for model, and normal matrix, 
  // as well as Phong shading related material properties
  class CollisionGeometry
  {
  public:
    OPENGL_EXPORTS CollisionGeometry();
    OPENGL_EXPORTS virtual ~CollisionGeometry();

    // Initialize by a set of vertex positions, vertex normals and triangle indices (starting from 0)
    OPENGL_EXPORTS void init(const std::vector<Vec3f>& p, const std::vector<Vec3f>& n, const std::vector<unsigned int>& t);
    OPENGL_EXPORTS void initInstance(std::shared_ptr<CollisionGeometry> original);

    OPENGL_EXPORTS void clear();

    // Returns the handle for the vertex array object (either original or instanced)
    OPENGL_EXPORTS GLuint handle() const;

    // Returns the number of triangle indices (either original or instanced)
    OPENGL_EXPORTS GLsizei numIndices() const;

    // Returns the model matrix
    OPENGL_EXPORTS Mat4x4f& modelMatrix(){return mModelMatrix;}

    // Computes and returns the origin position (modelMatrix*origin)
    OPENGL_EXPORTS Vec3f getPosition() const;

    // Set the light positions
    OPENGL_EXPORTS void setLightPosition0(const Vec3f& p) {mLightPosition[0]=Vec4f(p,1);}
    OPENGL_EXPORTS void setLightPosition1(const Vec3f& p) {mLightPosition[1]=Vec4f(p,1);}
    OPENGL_EXPORTS void setLightPosition2(const Vec3f& p) {mLightPosition[2]=Vec4f(p,1);}
    OPENGL_EXPORTS void setMaterial(float shininess, const Vec3f& color, float lineWidth=0.f, const Vec3f& lineColor=Vec3f(0,0,0));

    // Update data and upload it to the GPU
    OPENGL_EXPORTS void updateUniforms();

    // Bind the uniform buffer object for geometry and shading related properties
    OPENGL_EXPORTS void bind(const GLuint shaderProgram,const GLuint bindingPoint=0, const std::string &blockName="ub_Geometry") const;

    // Computes the point of intersection between ray and object.
    OPENGL_EXPORTS bool
      closestIntersection(const Ray &ray, float maxLambda, RayIntersection& intersetion) const;

    OPENGL_EXPORTS Ray transformRayWorldToModel(const Ray &ray) const
    {
        return ray.transformed(mModelMatrixInverse);
    }
    OPENGL_EXPORTS float transformRayLambdaWorldToModel(const Ray &ray, const float lambda) const
    {
      Vec3f model_direction = mModelMatrixInverse.as3x3()*ray.direction();
      return lambda * model_direction.length();
    }
    OPENGL_EXPORTS bool
      closestIntersectionModel(const Ray &ray, float maxLambda, RayIntersection& intersetion) const;

  private:
    bool   mInitialized;                          //< True if initialized

    //Transformation-related
    Mat4x4f   mModelMatrix;                          //< The model matrix.
    Mat4x4f   mModelMatrixInverse;                   //< The model matrix inverse.
    Mat4x4f   mModelMatrixInverseTransposed;        //< The model matrix inverse transposed.

    //GPU-related
    GLuint mIndexBuffer;                          //< Handle to the VBO storing triangle indices
    GLuint mPositionBuffer;                       //< Handle to the VBO storing vec3 positions
    GLuint mNormalBuffer;                         //< Handle to the VBO storing vec3 normals
    GLuint mVertexArrayObject;                    //< Handle to the VAO
    GLuint mUniformBuffer;                        //< Handle to the UBO for geometry and Phong properties
    GLsizei mNumIndices;                          //< Number of vertex triangle indices (size == 3*number_of_triangles)

    //Material-related
    float mShininess;                             //< Material shininess coefficient
    float mLineWidth;                             //< Material line width (for superimposed wireframe)
    Vec4f mColor;                                  //< Material color
    Vec4f mLineColor;                              //< Material line color (for superimposed wireframe)
    Vec4f mLightPosition[3];                       //< Three light positions

    //CPU Geometry-related
    std::vector<Vec3f> mCollisionPositions;
    std::vector<Vec3f> mCollisionNormals;
    std::vector<Vec3i> mCollisionIndices;
    std::shared_ptr<CollisionGeometry> mInstance;
    BVTree mCollisionTree;

  };
}

#endif //TRIANGLEGEOMETRY_HPP_INCLUDE_ONCE
