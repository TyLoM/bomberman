//
// Explosion.cpp for bomberman in /home/qu_a/bitbucket/bomberman/src
//
// Made by Antoine Qu
// Login   <qu_a@epitech.net>
//
// Started on  Sun Jun  7 14:32:46 2015 Antoine Qu
// Last update Sun Jun 14 21:34:53 2015 Antoine Qu
//

#include "Explosion.hpp"
#include "AEntity.hpp"
#include "Error.hpp"

Explosion::Explosion(const int x, const int y, const Entity type):
  AEntity(x, y, type), texPath(tex_explosion)
{
}

Explosion::~Explosion()
{
}

bool	Explosion::initGraph()
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

  scale *= glm::vec3(0.8, 0.8, 0.8);
  timer = 0.0;

  geometry.build();

  if (tex.load(texPath) == false)
    throw Error("Failed to load Cube texture.\n");
  return (true);
}

void		Explosion::pushUv()
{
  geometry.pushUv(glm::vec2(1.0f, 0.0f));
  geometry.pushUv(glm::vec2(1.0f, 1.0f));
  geometry.pushUv(glm::vec2(0.0f, 1.0f));
  geometry.pushUv(glm::vec2(0.0f, 0.0f));
}

void	Explosion::update(const gdl::Clock &_clock, gdl::Input &, Map *board)
{
  timer += _clock.getElapsed();
  if (timer > 0.5)
    board->deleteElement(getX(), getY(), getId());
}

void	Explosion::drawEntity(gdl::AShader &_shader, const gdl::Clock &)
{
  tex.bind();
  geometry.draw(_shader, getTransformation(), GL_QUADS);
}
