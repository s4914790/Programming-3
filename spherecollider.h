#ifndef SPHERE_H
#define SPHERE_H

#include "collider.h"

class BoxCollider;

class SphereCollider : public Collider
{
public:
  SphereCollider(float _radius, const ngl::Vec3 &_position = {0.0f, 0.0f, 0.0f});
  float radius() const;
  void setRadius(float radius);
  bool collides(const SphereCollider &sphere) const override;
  bool collides(const BoxCollider &box) const override;

private:
  float m_radius;
};

#endif // SPHERE_H
