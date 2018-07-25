#ifndef POINT_H
#define POINT_H

#include <ngl/Vec3.h>

class Point
{
public:
  Point(const ngl::Vec3 &_position = ngl::Vec3());
  const ngl::Vec3 &position() const;
  void setPosition(const ngl::Vec3 &_position);
  void move(const ngl::Vec3 &_delta, const float _deltaTime);

protected:
  ngl::Vec3 m_position;
};

#endif // POINT_H
