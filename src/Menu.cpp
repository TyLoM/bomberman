//
// Menu.cpp for qwe in /home/quentin/bucket/bomberman
//
// Made by Quentin Richard
// Login   <quentin@epitech.net>
//
// Started on  Fri May 29 17:26:15 2015 Quentin Richard
// Last update Sun Jun 14 21:49:32 2015 Quentin Richard
//

#include "Menu.hpp"
#include "Error.hpp"
#include <unistd.h>
#include "Game.hh"

Menu::Menu(GraphEngine *_win, Save *_save, AEntity *_pol)
{
  pos = glm::vec3(0, 0, 0);
  rot = glm::vec3(0, 0, 0);
  scale = glm::vec3(1, 1, 1);
  lvl = 0;
  check = 0;
  win = _win;
  save = _save;
  setMap = DEFAULT;
  nbPlayer = 1;
  nbAI = 0;
  soundM = 50;
  soundGame = 50;
  soundCreateMap = 50;
  heightMap = 10;
  widthMap = 10;
  pol = _pol;
}

Menu::~Menu()
{
}

bool		Menu::initGraph()
{
  if (tex.load(MENU_TEXTURE) == false)
    throw Error("Failed to load Menu texture.");
  if (tex2.load(MENU_GAME) == false)
    throw Error("Failed to load Menu texture.");
  if (tex3.load(MENU_BEFORE_GAME) == false)
    throw Error("Failed to load Menu texture.");
  if (tex4.load(CREATE_MENU) == false)
    throw Error("Failed to load Menu texture.");
  if (tex5.load(SCORE_MENU) == false)
    throw Error("Failed to load Score texture.");
  if (tex6.load(OPTION_MENU) == false)
    throw Error("Failed to load Option texture.");
  if (texLoad.load(LOADING) == false)
    throw Error("Failed to load Loading texture.");
  geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  pushUv();
  geometry.build();
  scale *= glm::vec3(1.0, 1.75, 1.0);
  learnFunction(&Menu::mainMenu);
  learnFunction(&Menu::selectMenu);
  learnFunction(&Menu::gameMenu);
  learnFunction(&Menu::createMapMenu);
  learnFunction(&Menu::scoreMenu);
  learnFunction(&Menu::optionMenu);
  nameMap.push_back("RANDOM");
  nameMap.push_back("PRESETA");
  nameMap.push_back("PRESETB");
  nameMap.push_back("YOUR MAP");
  tex.bind();
  sound = win->getSound(SDMENU);
  music.init(MSC_MENU);
  music.game();
  return true;
}

void	Menu::pushUv()
{
  geometry.pushUv(glm::vec2(1.0f, 0.0f));
  geometry.pushUv(glm::vec2(1.0f, 1.0f));
  geometry.pushUv(glm::vec2(0.0f, 1.0f));
  geometry.pushUv(glm::vec2(0.0f, 0.0f));
}

bool	Menu::update()
{
  if (win->update() == false)
    return false;
  if (win->getInput()->getKey(SDL_BUTTON_LEFT))
    {
      if (!(check = CALL_PTR_FUNCTION(*this, selectLvl[lvl])()))
	return false;
      save->setSaveFile(static_cast<SaveType>(setMap));
      return true;
    }
  check = 0;
  return true;
}

glm::mat4	Menu::getTransformation() const
{
  glm::mat4	matid(1);

  matid = glm::translate(matid, pos);

  matid = glm::rotate(matid, rot.x, glm::vec3(1, 0, 0));
  matid = glm::rotate(matid, rot.y, glm::vec3(0, 1, 0));
  matid = glm::rotate(matid, rot.z, glm::vec3(0, 0, 1));


  matid = glm::scale(matid, scale);
  return (matid);
}

void	Menu::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
  win->getShader()->setUniform("view", glm::lookAt(glm::vec3(2, 0, 0), glm::vec3(-4, 0, 0), glm::vec3(0, 0, 1)));
  geometry.draw(*(win->getShader()), getTransformation(), GL_QUADS);
  win->draw();
}
