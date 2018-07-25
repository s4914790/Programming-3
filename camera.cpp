#include "camera.h"

#include <ngl/Util.h>
#include <cmath>

Camera::Camera():
  Point()
{

}

Camera::Camera(const ngl::Vec3 &_position, const ngl::Vec3 &_look, const ngl::Vec3 &_up) noexcept :
  Point(_position)
{
  m_dirrection=_look;
  m_up=_up;

  updateCameraVectors();
}
// Sets camera parameters
void Camera::set(const ngl::Vec3 &_position, const ngl::Vec3 &_look, const ngl::Vec3 &_up) noexcept
{
  m_position=_position;
  m_dirrection=_look;
  m_up=_up;
  updateCameraVectors();
}
void Camera::setProjection(ngl::Real _fov, ngl::Real _aspect, ngl::Real _near, ngl::Real _far) noexcept
{
  m_zoom=_fov;
  m_aspect=_aspect;
  m_near=_near;
  m_far=_far;
  m_projection=ngl::perspective(_fov,_aspect,_near,_far);
}
//calculates and updates camera vectors when called
void Camera::updateCameraVectors() noexcept
{
  // Calculate the new Front vector
  m_forward.m_x = cosf(ngl::radians(m_yaw)) * cosf(ngl::radians(m_pitch));
  m_forward.m_y = sinf(ngl::radians(m_pitch));
  m_forward.m_z = sinf(ngl::radians(m_yaw)) * cosf(ngl::radians(m_pitch));
  m_forward.normalize();
  // Also re-calculate the Right and Up vector
  m_right = m_forward.cross(m_worldUp);  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
  m_up    = m_right.cross(m_forward);
  m_right.normalize();
  m_forward.normalize();
  m_view=ngl::lookAt(m_position, m_position + m_forward, m_up);

}

void Camera::move(const ngl::Vec3 &_deltaPos, float _deltaTime)
{
  Point::move(_deltaPos, _deltaTime);
  updateCameraVectors();
}

void Camera::rotate(float _horizontalOffset, float _verticalOffset, GLboolean _constrainPitch ) noexcept
{
  _horizontalOffset *= m_sensitivity;
  _verticalOffset *= m_sensitivity;

  m_yaw   += _horizontalOffset;
  m_pitch += _verticalOffset;

  // Make sure that when pitch is out of bounds, screen doesn't get flipped
  if (_constrainPitch)
    {
      if (m_pitch > 89.0f)
        m_pitch = 89.0f;
      if (m_pitch < -89.0f)
        m_pitch = -89.0f;
    }

  // Update Front, Right and Up Vectors using the updated Eular angles
  updateCameraVectors();
}

void Camera::zoom(float _yoffset) noexcept
{
  if (m_zoom >= 1.0f && m_zoom <= 45.0f)
    m_zoom -= _yoffset;
  if (m_zoom <= 1.0f)
    m_zoom = 1.0f;
  if (m_zoom >= 45.0f)
    m_zoom = 45.0f;
  m_projection=ngl::perspective(m_zoom,m_aspect,m_near,m_far);

}

const ngl::Vec3 &Camera::forward() const
{
  return m_forward;
}

const ngl::Vec3 &Camera::right() const
{
  return m_right;
}

const ngl::Vec3 &Camera::up() const
{
  return m_up;
}
