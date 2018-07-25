#include "spherecollider.h"
#include "boxcollider.h"

SphereCollider::SphereCollider(float _radius, const ngl::Vec3 &_position):
  Collider(_position),
  m_radius(_radius)
{

}

float SphereCollider::radius() const
{
  return m_radius;
}

void SphereCollider::setRadius(float radius)
{
  m_radius = radius;
}

bool SphereCollider::collides(const SphereCollider &sphere) const
{
  return (position() - sphere.position()).length() < (radius() + sphere.radius());
}

bool SphereCollider::collides(const BoxCollider &_box) const
{
  auto &sphereCenter = position();
  auto boxHalfSizes = (_box.sizes() / 2);
  auto &boxCenter = _box.position();
  ngl::Vec3 boxClosestPoint {std::max(boxCenter[0] - boxHalfSizes[0], std::min(sphereCenter[0], boxCenter[0] + boxHalfSizes[0])),
        std::max(boxCenter[1] - boxHalfSizes[1], std::min(sphereCenter[1], boxCenter[1] + boxHalfSizes[1])),
        std::max(boxCenter[2] - boxHalfSizes[2], std::min(sphereCenter[2], boxCenter[2] + boxHalfSizes[2]))};

  auto distanceVector = sphereCenter - boxClosestPoint;

  return (distanceVector.length() <= radius());
}
