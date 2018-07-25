#ifndef COLLIDER_H
#define COLLIDER_H

#include "point.h"

class BoxCollider;
class SphereCollider;

class Collider : public Point
{
public:
  Collider(const ngl::Vec3 &_position);
  virtual ~Collider() = default;
  bool collides(const Collider &) const;
  virtual bool collides(const BoxCollider &_box) const = 0;
  virtual bool collides(const SphereCollider &_sphere) const = 0;
};

#endif // COLLIDER_H
