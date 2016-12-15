//
// GameEngine.cpp for Bomberman in /home/mcnama_d/gitreps/B4-CPP/test_bomberman/src
//
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
//
// Started on  Thu Jun  4 21:22:30 2015 Duncan McNAMARA
// Last update Sun Jun 14 23:15:42 2015 Duncan McNAMARA
//

#include <unistd.h>
#include "GameEngine.hpp"
#include "Error.hpp"

GameEngine::GameEngine(GraphEngine *_toGraph, Save *_save,
		       const unsigned int _nbPlayers,
		       const unsigned int,
		       const unsigned int _volume,
		       const SaveType _saveType)
  : toGraph(_toGraph), save(_save), nbPlayers(_nbPlayers), nbAi(0),
    volume(_volume), saveType(_saveType), pause(false)
{
  skin = new Texture;
  music = new Music;
}

GameEngine::~GameEngine()
{
  delete skin;
  delete testmap;
  delete music;
  delete back;
  delete ground;
}

bool	GameEngine::initialize()
{
  skin->initialize();
  ground = new Box(0, 0, skin, GROUND);
  back = new Box(0, 0, skin, BACKGROUND);
  if (save->getState() == false)
    {
      testmap = new Map(10, 10, skin);
      testmap->setNbPlayer(nbPlayers);
      testmap->setNbAi(nbAi);
      testmap->genTotalPlayer();
      testmap->generateMap(static_cast<MapTypes>(saveType));
      if ((marvin = testmap->spawnChar(1)) == NULL)
	  throw Error("Failed to spawn Player 1");
      if (nbPlayers == 2)
	{
	  if ((marvin2 = testmap->spawnChar(2)) == NULL)
	    throw Error("Failed to spawn Player 2");
	}
    }
  else
    {
      if ((testmap = getSave()->loadFile(saveType)) == NULL)
	throw Error("Failed to load file");
      testmap->setNbPlayer(nbPlayers);
      testmap->setNbAi(nbAi);
      testmap->genTotalPlayer();
      if (nbPlayers == 2)
	{
	  if ((marvin2 = findCharacter(2)) == NULL)
	    if ((marvin2 = testmap->spawnChar(2)) == NULL)
	      throw Error("Failed to spawn Player");
	}
      if ((marvin = findCharacter(1)) == NULL)
	if ((marvin = testmap->spawnChar(1)) == NULL)
	  throw Error("Failed to spawn Player");
    }
  for (unsigned int i = 0 ; i < nbAi ; ++i)
    if (!testmap->spawnChar(0))
      throw Error("Failed to spawn AI");
  back->initGraph();
  back->ftranslate(glm::vec3(testmap->getWidth() / 2, testmap->getHeight() / 2, 0));
  back->fscale(glm::vec3(testmap->getWidth() * 2, testmap->getHeight() * 2,
			 testmap->getWidth() + testmap->getHeight()));
  ground->initGraph();
  ground->fscale(glm::vec3(testmap->getWidth() + 1, testmap->getHeight() + 1, 1));
  ground->ftranslate(glm::vec3((testmap->getWidth() + 2) / 2, (testmap->getHeight() + 2) / 2, 0));
  testmap->setSound(toGraph->getPtrSound());
  music->init(MSC_GAME);
  music->setVolumeMusic(volume);
  music->game();
  toGraph->getSound(SDSTART)->play();

  return false;
}

void		GameEngine::endDraw(Entity _type)
{
  AEntity	*screen = new Box(0, 0, skin, _type);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
  toGraph->getShader()->setUniform("view", glm::lookAt(glm::vec3(2, 0, 0), glm::vec3(-4, 0, 0), glm::vec3(0, 0, 1)));
  screen->initGraph();
  screen->drawEntity(*(toGraph->getShader()), toGraph->getClock());
  toGraph->draw();
  sleep(3);
}

bool	GameEngine::endGame()
{
  int	ttpl = testmap->getTotalPlayer();

  if (ttpl == 1 && nbPlayers != 1)
    {
      if (testmap->getLastTeam() >= 1)
	endDraw(YOUWIN);
      else
	endDraw(YOULOSE);
      return (false);
    }
  else if (ttpl == 0)
    {
      endDraw(YOULOSE);
      return (false);
    }
  return (true);
}

bool	GameEngine::update()
{
  if (pause == false)
    {
      toGraph->update();
      if (!endGame())
	return false;
      if (toGraph->getInput()->getKey(SDLK_ESCAPE))
	return false;
      if (toGraph->getInput()->getKey(SDLK_p, true))
	{
	  pause = true;
	  return (true);
	}
      testmap->updateMap(*(toGraph->getShader()), toGraph->getClock(),
			 *(toGraph->getInput()), marvin->getPos() + glm::vec3(0, -2, 6));
      if (toGraph->getInput()->getKey(SDLK_ESCAPE) || toGraph->getInput()->getKey(SDL_QUIT))
	return false;
      checkSave();
    }
  else
    {
      toGraph->getCtxt().updateInputs(*(toGraph->getInput()));
      if (toGraph->getInput()->getKey(SDLK_p, true))
	pause = false;
    }
  return true;
}

void	GameEngine::draw()
{
  if (pause == false)
    {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      if (nbPlayers == 1)
	onePlayerDraw();
      else
	twoPlayerDraw();

      toGraph->draw();
    }
}

void	GameEngine::onePlayerDraw()
{
  toGraph->getShader()->setUniform("view", glm::lookAt(marvin->getPos() + glm::vec3(0, -2, 10),
  					marvin->getPos(), glm::vec3(0, 0, 1)));
  testmap->displayMap(*(toGraph->getShader()), toGraph->getClock(),
  		      *(toGraph->getInput()), marvin->getPos() + glm::vec3(0, -2, 10));
  back->drawEntity(*(toGraph->getShader()), toGraph->getClock());
  ground->drawEntity(*(toGraph->getShader()), toGraph->getClock());
}

void	GameEngine::twoPlayerDraw()
{
  toGraph->getShader()->setUniform("view", glm::lookAt(marvin->getPos() + glm::vec3(0, -2, 10),
  					marvin->getPos(), glm::vec3(0, 0, 1)));
  glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT / 2);

  testmap->displayMap(*(toGraph->getShader()), toGraph->getClock(),
  		      *(toGraph->getInput()), marvin->getPos() + glm::vec3(0, -2, 10));
  back->drawEntity(*(toGraph->getShader()), toGraph->getClock());
  ground->drawEntity(*(toGraph->getShader()), toGraph->getClock());

  glViewport(0, WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT / 2);
  toGraph->getShader()->setUniform("view", glm::lookAt(marvin2->getPos() + glm::vec3(0, -2, 10),
  					marvin2->getPos(), glm::vec3(0, 0, 1)));
  testmap->displayMap(*(toGraph->getShader()), toGraph->getClock(),
  		      *(toGraph->getInput()), marvin2->getPos() + glm::vec3(0, -2, 10));
  back->drawEntity(*(toGraph->getShader()), toGraph->getClock());
  ground->drawEntity(*(toGraph->getShader()), toGraph->getClock());
}

void	GameEngine::checkSave()
{
  if (toGraph->getInput()->getKey(SDLK_x, true))
    getSave()->saveFile(getMap(), SAVE);
}

AEntity				*GameEngine::findCharacter(const int team)
{
  std::vector<AEntity *>	**board = testmap->getBoard();


  for (int y = 1; y < testmap->getHeight() + 1; ++y)
    for (int x = 1; x < testmap->getWidth() + 1; ++x)
      for (auto iterator = board[y][x].begin(); iterator != board[y][x].end(); ++iterator)
	if ((*iterator)->getType() == PLAYER)
	  {
	    if (static_cast<Character*>(*iterator)->getTeam() == team)
	      return (*iterator);
	  }
  return (NULL);
}

void	GameEngine::setNbPlayers(const int _nbPlayers)
{
  nbPlayers = _nbPlayers;
}


void	GameEngine::setNbAi(const int _nbAi)
{
  nbAi = _nbAi;
}

Save   	*GameEngine::getSave() const
{
  return (save);
}

Map	*GameEngine::getMap() const
{
  return (testmap);
}
