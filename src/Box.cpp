//
// Box.cpp for bomberman in /home/qu_a/bitbucket/bomberman/src
//
// Made by Antoine Qu
// Login   <qu_a@epitech.net>
//
// Started on  Fri May 22 16:37:39 2015 Antoine Qu
// Last update Sun Jun 14 22:05:58 2015 Duncan McNAMARA
//

#include "Box.hpp"
#include "Error.hpp"


Box::Box(const int x, const int y, Texture *_skin, const Entity _type)
  : AEntity(x, y, _type), texPath(_skin->getPath(_type))
{
}

Box::~Box()
{
}

bool		Box::initGraph()
{
  if (tex.load(texPath) == false)
    throw Error("Failed to load Cube texture");

  geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  pushUv();
  if (type != VOID_BLOCK && type != GROUND &&
      type != YOUWIN && type != YOULOSE)
    {
      geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
      geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
      geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
      geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
      pushUv();
      geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
      geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
      geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
      geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
      pushUv();
      geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
      geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
      geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
      geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
      pushUv();
      geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
      geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
      geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
      geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
      pushUv();
      geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
      geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
      geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
      geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
      pushUv();
    }
  if (type == YOUWIN || type == YOULOSE)
    {
      rot += glm::vec3(0, 90, 0);
      scale *= glm::vec3(1.0, 1.75, 1.0);
    }
  if (getType() == CURSOR1 || getType() == CURSOR2)
    changeToCursor();
  else
    geometry.build();
  return (true);
}

void		Box::pushUv()
{
  geometry.pushUv(glm::vec2(0.0f, 0.0f));
  geometry.pushUv(glm::vec2(1.0f, 0.0f));
  geometry.pushUv(glm::vec2(1.0f, 1.0f));
  geometry.pushUv(glm::vec2(0.0f, 1.0f));
}

void		Box::update(const gdl::Clock &, gdl::Input &, Map *)
{
  if (getType() == CURSOR1 || getType() == CURSOR2)
    rot += glm::vec3(0, 0, 1);
}

void		Box::drawEntity(gdl::AShader &_shader, const gdl::Clock &)
{
  tex.bind();
  geometry.draw(_shader, getTransformation(), GL_QUADS);
}

void		Box::changeToCursor()
{
  rot += glm::vec3(0, 0, 45);
  scale *= glm::vec3(0.25, 0.25, 0.25);
  pos += glm::vec3(0.0, 0.0, 1.3);
  geometry.build();
}
