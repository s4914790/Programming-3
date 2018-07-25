#include "boxcollider.h"
#include "spherecollider.h"

BoxCollider::BoxCollider(const ngl::Vec3 &_sizes, const ngl::Vec3 &_position):
  Collider(_position),
  m_sizes(_sizes)
{

}

const ngl::Vec3 &BoxCollider::sizes() const
{
  return m_sizes;
}

void BoxCollider::setSizes(const ngl::Vec3 &sizes)
{
  m_sizes = sizes;
}

bool BoxCollider::collides(const BoxCollider &_box) const
{
  auto halfSizes = (sizes() / 2);
  auto minPoint = position() - halfSizes;
  auto maxPoint = position() + halfSizes;
  auto boxHalfSizes = _box.sizes() / 2;
  auto boxMinPoint = _box.position() - boxHalfSizes;
  auto boxMaxPoint = _box.position() + boxHalfSizes;
  return
      ((minPoint[0] <= boxMaxPoint[0] && maxPoint[0] >= boxMinPoint[0]) &&
      (minPoint[1] <= boxMaxPoint[1] && maxPoint[1] >= boxMinPoint[1]) &&
      (minPoint[2] <= boxMaxPoint[2] && maxPoint[2] >= boxMinPoint[2]));
}

bool BoxCollider::collides(const SphereCollider &sphere) const
{
  return sphere.collides(*this);
}
