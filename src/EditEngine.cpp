//
// EditEngine.cpp for Bomberman in /home/mcnama_d/gitreps/B4-CPP/bomberman/src
//
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
//
// Started on  Tue Jun  9 15:37:25 2015 Duncan McNAMARA
// Last update Sun Jun 14 19:21:14 2015 Duncan McNAMARA
//

#include "EditEngine.hpp"
#include "Error.hpp"

EditEngine::EditEngine(GraphEngine *_toGraph, Save *_save, unsigned int _volume)
  : toGraph(_toGraph), save(_save), volume(_volume)
{
  skin = new Texture;
  skin->initialize();
  box = new EditBox(skin);
  music = new Music;
  back = new Box(0, 0, skin, BACKGROUND);
}

EditEngine::~EditEngine()
{
  music->end();
  delete skin;
  delete music;
}

bool	EditEngine::initialize(const unsigned int _width, const unsigned int _height)
{
  board = new Map(_width, _height, skin);
  board->generateMap(CUSTOM);
  box->initialize();
  back->initGraph();
  back->ftranslate(glm::vec3(board->getWidth() / 2, board->getHeight() / 2, 0));
  back->fscale(glm::vec3(board->getWidth() * 2 , board->getHeight() * 2,
			 board->getWidth() + board->getHeight()));
  music->init(MSC_EDITOR);
  music->setVolumeMusic(volume);
  music->game();
  return true;
}

bool	EditEngine::update()
{
  toGraph->update();
  if (toGraph->getInput()->getKey(SDLK_ESCAPE))
    return false;
  if (toGraph->getInput()->getKey(SDLK_KP_ENTER) ||
      toGraph->getInput()->getKey(SDLK_RETURN))
    {
      std::cout << "Saving ..." << std::endl;
      save->saveFile(board, MAP);
      return false;
    }
  else if (toGraph->getInput()->getKey(SDLK_ESCAPE) || toGraph->getInput()->getKey(SDL_QUIT))
    return false;
  box->update(toGraph->getClock(), *(toGraph->getInput()), board);
  return true;
}

void	EditEngine::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);

  toGraph->getShader()->setUniform("view", glm::lookAt(box->getPos() + glm::vec3(0, -4, 8),
						       box->getPos(), glm::vec3(0, 0, 1)));
  board->displayMap(*(toGraph->getShader()), toGraph->getClock(),
		    *(toGraph->getInput()), box->getPos() + glm::vec3(0, -5, 5));
  box->draw(*(toGraph->getShader()), toGraph->getClock());
  back->drawEntity(*(toGraph->getShader()), toGraph->getClock());
  toGraph->draw();
}

void	EditEngine::checkSave()
{
  if (toGraph->getInput()->getKey(SDLK_x, true))
    getSave()->saveFile(getMap(), MAP);
}

Save   	*EditEngine::getSave() const
{
  return (save);
}

Map	*EditEngine::getMap() const
{
  return (board);
}
