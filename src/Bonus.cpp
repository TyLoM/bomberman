//
// Bonus.cpp for bomberman in /home/qu_a/bitbucket/bomberman/src
//
// Made by Antoine Qu
// Login   <qu_a@epitech.net>
//
// Started on  Sat May 23 16:58:27 2015 Antoine Qu
// Last update Sun Jun 14 21:24:27 2015 Antoine Qu
//

#include "Bonus.hpp"
#include "Error.hpp"

Bonus::Bonus(const int x, const int y, Texture *_skin, const Entity _type)
  : AEntity(x, y, _type), texPath(_skin->getPath(_type))
{
}

Bonus::~Bonus()
{
}

bool            Bonus::initGraph()
{
  //up
  geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  pushUv();
  //down
  geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  pushUv();
  //right
  geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  pushUv();
  //left
  geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  pushUv();
  //rear
  geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  pushUv();
  //front
  geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  pushUv();

  pos += glm::vec3(0, 0, 0.25);
  scale *= glm::vec3(0.5, 0.5, 0.5);

  geometry.build();

  if (tex.load(texPath) == false)
    throw Error("Failed to load Cube texture.\n");
  return (true);
}

void		Bonus::pushUv()
{
  geometry.pushUv(glm::vec2(1.0f, 0.0f));
  geometry.pushUv(glm::vec2(1.0f, 1.0f));
  geometry.pushUv(glm::vec2(0.0f, 1.0f));
  geometry.pushUv(glm::vec2(0.0f, 0.0f));
}

void		Bonus::drawEntity(gdl::AShader &_shader, const gdl::Clock &)
{
  tex.bind();
  geometry.draw(_shader, getTransformation(), GL_QUADS);
}

void		Bonus::update(const gdl::Clock &, gdl::Input &, Map *)
{
  frotate(glm::vec3(0, 0, 1), 1);
}
