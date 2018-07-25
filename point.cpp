#include "point.h"

Point::Point(const ngl::Vec3 &_position):
  m_position(_position){}

const ngl::Vec3 &Point::position() const
{
  return m_position;
}

void Point::setPosition(const ngl::Vec3 &_position)
{
  m_position = _position;
}

void Point::move(const ngl::Vec3 &_deltaPos, const float _deltaTime)
{
  m_position += _deltaPos * _deltaTime;
}
