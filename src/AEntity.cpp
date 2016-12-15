//
// AEntity.cpp for qwe in /home/lee_c/gitdepot/bomberman/src
//
// Made by soomin lee
// Login   <lee_c@epitech.net>
//
// Started on  Fri May 22 15:41:19 2015 soomin lee
// Last update Sun Jun 14 22:31:22 2015 david tang
//

#include "AEntity.hpp"

AEntity::AEntity(const int _x, const int _y, const Entity _type, const int _id)
  : id(_id), type(_type), pos(_x, _y, 0), rot(0, 0, 0), scale(1, 1, 1)
{
}

AEntity::~AEntity()
{
}

int	AEntity::getX(void) const
{
  return pos.x;
}

int	AEntity::getY(void) const
{
  return pos.y;
}

int	AEntity::getId(void) const
{
  return id;
}

Entity	AEntity::getType(void) const
{
  return type;
}

glm::vec3	AEntity::getPos(void) const
{
  return (pos);
}

void	AEntity::setId(const int value)
{
  id = value;
}

void	AEntity::ftranslate(const glm::vec3 &_v)
{
  pos += _v;
}

void	AEntity::frotate(const glm::vec3 &_axis, const float _angle)
{
  rot += _axis * _angle;
}

void	AEntity::fscale(const glm::vec3 &_scale)
{
  scale *= _scale;
}

glm::mat4	AEntity::getTransformation() const
{
  glm::mat4	matid(1);

  matid = glm::translate(matid, pos);
  matid = glm::rotate(matid, rot.x, glm::vec3(1, 0, 0));
  matid = glm::rotate(matid, rot.y, glm::vec3(0, 1, 0));
  matid = glm::rotate(matid, rot.z, glm::vec3(0, 0, 1));
  matid = glm::scale(matid, scale);
  return (matid);
}
