#include "texturedmesh.h"

#include <ngl/Transformation.h>
#include <ngl/ShaderLib.h>
#include <iostream>

#include "texturepack.h"

TexturedMesh::TexturedMesh(const std::string &_objFile,
                     const std::string &_textureName,
                     const ngl::Vec3 &_position):
  Point(_position),
  m_object(_objFile),
  m_textureName(_textureName)
{
  m_object.createVAO();
}

void TexturedMesh::paintGL(const Camera &camera)
{
  auto shader = ngl::ShaderLib::instance();
  ngl::Transformation transformation;
  transformation.setPosition(m_position);
  ngl::Mat4 M = transformation.getMatrix();
  ngl::Mat4 MV = camera.getView();
  ngl::Mat4 MVP = camera.getVP() * M;
  ngl::Mat3 N = MV;

  N.inverse().transpose();
  shader->setUniform( "MVP", MVP );
  shader->setUniform( "N", N );
  shader->setUniform( "M", M );
  shader->setUniform("camPos", camera.position());
  TexturePack::activateTexturePack(m_textureName);
  m_object.draw();
}
