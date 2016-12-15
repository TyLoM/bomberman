//
// GraphEngine.cpp for Bomberman in /home/mcnama_d/gitreps/B4-CPP/test_bomberman/src
// 
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
// 
// Started on  Thu Jun  4 21:13:47 2015 Duncan McNAMARA
// Last update Sat Jun 13 12:04:15 2015 Duncan McNAMARA
//

#include "GraphEngine.hpp"
#include "Error.hpp"
#include "Character.hpp"
#include "Bonus.hpp"

GraphEngine::GraphEngine() {}

GraphEngine::~GraphEngine()
{
  ctxt.stop();
}

bool			GraphEngine::initialize()
{
  if (ctxt.start(WIN_WIDTH, WIN_HEIGHT, "Bomberman !") == false)
    {
      throw Error("Call to gdl::start has failed");
      return false;
    }

  glEnable(GL_DEPTH_TEST);

  if (!shader.load("../LibBomberman_linux_x64/shaders/basic.fp", GL_FRAGMENT_SHADER) ||
      !shader.load("../LibBomberman_linux_x64/shaders/basic.vp", GL_VERTEX_SHADER) ||
      !shader.build())
    throw Error("Failed to load shaders.");
  shader.bind();
  shader.setUniform("projection", glm::perspective(60.0f, 1024.0f / 768.0f, 0.1f, 100.0f));

  sound = new Sound();
  if (!sound->init())
    throw Error("Failed to initiate sounds");
  return true;
}

bool			GraphEngine::update()
{
  ctxt.updateInputs(input);
  ctxt.updateClock(clock);
  if (input.getKey(SDL_QUIT))
    return (false);
  return true;
}

void			GraphEngine::draw()
{
  ctxt.flush();
}

gdl::SdlContext		GraphEngine::getCtxt() const
{
  return ctxt;
}

gdl::Input		*GraphEngine::getInput()
{
  return &input;
}

gdl::Clock		GraphEngine::getClock() const
{
  return clock;
}

gdl::BasicShader	*GraphEngine::getShader()
{
  return &shader;
}

sf::Music		*GraphEngine::getSound(Sounds type)
{
  return (sound->getSound(type));
}

Sound			*GraphEngine::getPtrSound(void)
{
  return (sound);
}
