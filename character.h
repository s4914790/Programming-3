#ifndef CHARACTER_H
#define CHARACTER_H

#include "pawn.h"

class Character : public Pawn
{
public:
  using Pawn::move;
  using Pawn::camera;
  Character(Scene *_scene, const ngl::Vec3& _position = ngl::Vec3());
  void move(float _forward, float _rigth, float _deltaTime);
};

#endif // CHARACTER_H
