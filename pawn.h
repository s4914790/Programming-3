#ifndef PAWN_H
#define PAWN_H

#include "actor.h"
#include "camera.h"

class Pawn : public Actor
{
public:
  Pawn(Scene *_scene, const ngl::Vec3& _position = ngl::Vec3());
  void setPosition(const ngl::Vec3 &_position);
  void move(const ngl::Vec3 &_deltaPos, float _deltaTime);
  void move(float _forward, float _rigth, float _deltaTime);
  void rotate(float _horizontalOffset, float _verticalOffset, GLboolean constrainPitch = true);
  const Camera &camera() const;
  void setCameraProjection(ngl::Real _fov, ngl::Real _aspect, ngl::Real _near, ngl::Real _far);

protected:
  float m_speed = 5.0f;
  Camera m_camera;
};

#endif // PAWN_H
