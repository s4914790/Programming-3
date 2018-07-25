#ifndef MESHACTOR_H
#define MESHACTOR_H

#include "point.h"

#include <ngl/Obj.h>

#include "camera.h"

class TexturedMesh : public Point
{
public:
  TexturedMesh(const std::string &_objFile, const std::string &_textureName, const ngl::Vec3& _position = {0, 0, 0});
  void paintGL(const Camera &camera);

private:
  ngl::Obj m_object;
  std::string m_textureName;
};

#endif // MESHACTOR_H
