#ifndef CAMERA_H
#define CAMERA_H

#include "point.h"

#include <ngl/Mat4.h>

class Camera : public Point
{
public :
  Camera();
  Camera(const ngl::Vec3 &_position, const ngl::Vec3 &_look, const ngl::Vec3 &_up=ngl::Vec3::up()) noexcept;
  void set(const ngl::Vec3 &_position, const ngl::Vec3 &_look, const ngl::Vec3 &_up=ngl::Vec3::up()) noexcept;
  void setProjection(ngl::Real _fov, ngl::Real _aspect, ngl::Real _near, ngl::Real _far) noexcept;
  ngl::Mat4 getView() const noexcept { return m_view;}
  ngl::Mat4 getProjection() const noexcept {return m_projection;}
  ngl::Mat4 getVP() const noexcept{return m_projection*m_view;}
  ngl::Vec3 position() const noexcept { return m_position;}
  void updateCameraVectors() noexcept;

  void move(const ngl::Vec3 &_deltaPos, float _deltaTime);
  void move(float _x, float _y, float _deltaTime);
  void rotate(float _horizontalOffset, float _verticalOffset, GLboolean constrainPitch = true) noexcept;
  void zoom(float _yoffset) noexcept;
  const ngl::Vec3 &forward() const;
  const ngl::Vec3 &right() const;
  const ngl::Vec3 &up() const;

private :
  ngl::Mat4 m_view;
  ngl::Mat4 m_projection;
  ngl::Vec3 m_dirrection={0,0,0};
  ngl::Vec3 m_worldUp={0,1,0};
  ngl::Vec3 m_forward;
  ngl::Vec3 m_right;
  ngl::Vec3 m_up;
  ngl::Real m_yaw=-90.0f;
  ngl::Real m_pitch=0.0f;
  ngl::Real m_speed=2.5f;
  ngl::Real m_sensitivity=0.1f;
  ngl::Real m_zoom=45.0f;
  ngl::Real m_near=0.1f;
  ngl::Real m_far=100.0f;
  ngl::Real m_aspect=1.2f;
};

#endif // CAMERA_H
