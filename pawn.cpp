#include "pawn.h"

#include <iostream>
#include "spherecollider.h"

Pawn::Pawn(Scene *_scene, const ngl::Vec3 &_position):
  Actor (_scene, _position),
  m_camera(_position, {0, 0, 0}, {0, 1, 0})
{
  setCameraProjection( 45.0f, 720.0f / 576.0f, 0.05f, 350.0f );
  setCollider(new SphereCollider(1));
}

void Pawn::setPosition(const ngl::Vec3 &_position)
{
  auto deltaPosition = _position - m_position;
  Actor::setPosition(_position);
  m_camera.setPosition(m_camera.position() + deltaPosition);
}

void Pawn::move(const ngl::Vec3 &_deltaPos, float _deltaTime)
{
  if (Actor::move(_deltaPos, _deltaTime))
    {
      m_camera.move(_deltaPos, _deltaTime);
    }
}

void Pawn::move(float _forward, float _rigth, float _deltaTime)
{
  auto moveVector = (m_camera.forward() * _forward + m_camera.right() * _rigth) * m_speed;
  move(moveVector, _deltaTime);
}

void Pawn::rotate(float _horizontalOffset, float _verticalOffset, GLboolean constrainPitch)
{
 m_camera.rotate(_horizontalOffset, _verticalOffset, constrainPitch);
}

const Camera &Pawn::camera() const
{
  return m_camera;
}

void Pawn::setCameraProjection(ngl::Real _fov, ngl::Real _aspect, ngl::Real _near, ngl::Real _far)
{
  m_camera.setProjection(_fov, _aspect, _near, _far);
}
