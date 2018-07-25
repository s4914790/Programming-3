#include "character.h"

Character::Character(Scene *_scene, const ngl::Vec3 &_position):
  Pawn(_scene, _position)
{

}

void Character::move(float _forward, float _rigth, float _deltaTime)
{
  auto characterForward = m_camera.forward();
  characterForward[1] = 0;
  characterForward.normalize();
  auto moveVector = (characterForward * _forward + m_camera.right() * _rigth) * m_speed;
  Pawn::move(moveVector, _deltaTime);
}
