#ifndef ACTOR_H
#define ACTOR_H

#include "texturedmesh.h"
#include "collider.h"

class Scene;

class Actor : public Point
{
public:
  Actor(Scene *_scene, const ngl::Vec3& _position = ngl::Vec3());
  Actor(Scene *_scene, TexturedMesh *_texturedMesh = nullptr, Collider *_collider = nullptr, const ngl::Vec3& _position = ngl::Vec3());
  void paintGL();
  void setTexturedMesh(TexturedMesh *_texturedMesh);
  const TexturedMesh *texturedMesh() const;
  void setCollider(Collider *_collider);
  const Collider *collider() const;
  void setPosition(const ngl::Vec3 &position);
  bool move(const ngl::Vec3 &_deltaPos, float _deltaTime);



private:
  Scene *m_scene;
  std::unique_ptr<TexturedMesh> m_texturedMesh;
  std::unique_ptr<Collider> m_collider;

  void moveChilds(const ngl::Vec3 &delta);
};

#endif // ACTOR_H
