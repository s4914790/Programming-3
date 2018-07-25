#include "collider.h"

#include "spherecollider.h"
#include "boxcollider.h"

Collider::Collider(const ngl::Vec3 &_position):
  Point(_position)
{

}

bool Collider::collides(const Collider &_collider) const
{
  auto sphereCollider = dynamic_cast<const SphereCollider*>(&_collider);
  if (sphereCollider)
    {
      return collides(*sphereCollider);
    }
  auto boxCollider = dynamic_cast<const BoxCollider*>(&_collider);
  if (boxCollider)
    {
      return collides(*boxCollider);
    }
}
