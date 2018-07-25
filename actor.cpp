#include "actor.h"

#include <iostream>
#include <ngl/NGLStream.h>
#include "scene.h"


Actor::Actor(Scene *_scene, const ngl::Vec3 &_position):
  Point(_position),
  m_scene(_scene)
{

}

Actor::Actor(Scene *_scene, TexturedMesh *_texturedMesh, Collider *_collider, const ngl::Vec3 &_position):
  Point(_position),
  m_scene(_scene)
{
  if (_texturedMesh) setTexturedMesh(_texturedMesh);
  if (_collider) setCollider(_collider);
}

void Actor::paintGL()
{
  if (m_texturedMesh) m_texturedMesh->paintGL(m_scene->player().camera());
}

void Actor::setTexturedMesh(TexturedMesh *_texturedMesh)
{
  _texturedMesh->setPosition(_texturedMesh->position() + m_position);
  m_texturedMesh.reset(_texturedMesh);
}

const TexturedMesh *Actor::texturedMesh() const
{
  return m_texturedMesh.get();
}

void Actor::setCollider(Collider *_collider)
{
  _collider->setPosition(_collider->position() + position());
  m_collider.reset(_collider);
}
const Collider *Actor::collider() const
{
  return m_collider.get();
}

void Actor::setPosition(const ngl::Vec3 &_position)
{
  auto deltaPosition = _position - m_position;
  Point::setPosition(_position);
  if (m_texturedMesh) m_texturedMesh->setPosition(m_texturedMesh->position() + deltaPosition);
  if (m_collider) m_collider->setPosition(m_texturedMesh->position() + deltaPosition);
}

bool Actor::move(const ngl::Vec3 &_deltaPos, float _deltaTime)
{
  std::cout << "Move: " << _deltaPos << std::endl;
  if (m_collider)
    {
      m_collider->move(_deltaPos, _deltaTime);
      for (auto &actor : m_scene->actors())
        {
          if (this != actor.get() && actor->collider() && m_collider->collides(*actor->collider()))
            {
              m_collider->move(-_deltaPos, _deltaTime);
              std::cout << "Collistion detected. Unable to move" << std::endl;
              return false;
            }
        }
    }

  Point::move(_deltaPos, _deltaTime);
  if (m_texturedMesh) m_texturedMesh->move(_deltaPos, _deltaTime);
  std::cout << "New position: " << m_position <<std::endl;
  return true;
}
