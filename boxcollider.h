#ifndef BOX_H
#define BOX_H

#include "collider.h"

class SphereCollider;

class BoxCollider : public Collider
{
public:
  BoxCollider(const ngl::Vec3 &_sizes, const ngl::Vec3 &_position = {0.0f, 0.0f, 0.0f});
  const ngl::Vec3 &sizes() const;
  void setSizes(const ngl::Vec3 &sizes);
  bool collides(const BoxCollider &box) const override;
  bool collides(const SphereCollider &sphere) const override;

private:
  ngl::Vec3 m_sizes;
};

#endif // BOX_H
