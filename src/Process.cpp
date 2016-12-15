//
// Process.cpp for qwe in /home/quentin/bucket/bomberman
//
// Made by Quentin Richard
// Login   <quentin@epitech.net>
//
// Started on  Mon Jun  1 17:21:36 2015 Quentin Richard
// Last update Sun Jun 14 21:59:13 2015 david tang
//

#include "Menu.hpp"
#include "Process.hpp"
#include "EditEngine.hpp"
#include "GameEngine.hpp"
#include "Error.hpp"

Process::Process(GraphEngine *_win, Save *_save)
{
  win = _win;
  save = _save;
}

Process::~Process()
{}

bool	Process::goMenu(AEntity *pol)
{
  Menu	wel(win, save, pol);

  try
    {
      wel.initGraph();
      while (wel.update() == true)
	wel.draw();
    }
  catch (const Error &error)
    {
      std::cerr << "Error : " << error.what() << std::endl;
    }
  return false;
}

bool		Process::goGame(const int &nbPlayer, const int &nbAI, const int &volumeSound, const SaveType &saveType)
{
  if (save->fileExist(saveType) == false)
    {
      save->setState(false);
      std::cerr << "There is no saved file." << std::endl;
      return (false);
    }
  try
    {
      GameEngine	game(win, save, nbPlayer, nbAI, volumeSound, saveType);

      if (save->getSaveFile() == MAP)
	{
	  // game.setNbPlayers(nbPlayer);
	  // game.setNbAi(nbAI);
	  save->setState(true);
	}
      else
	save->setState(false);
      game.initialize();
      while (game.update() == true)
	game.draw();
      save->setState(false);
      return true;
    }
  catch (const Error &error)
    {
      std::cerr << "Error : " << error.what() << std::endl;
      return true;
    }
  return false;
}

bool		Process::goLoad()
{
  if (save->fileExist(SAVE) == false)
    {
      save->setState(false);
      std::cerr << "There is no saved file." << std::endl;
      return (false);
    }
  try
    {
      GameEngine game(win, save, 1, 1, 50, SAVE);
      game.initialize();
      while (game.update() == true)
	game.draw();
      return true;
    }
  catch (const Error &error)
    {
      std::cerr << "Error : " << error.what() << std::endl;
      return true;
    }
  return false;
}

bool	Process::goCreateMap(const int &width, const int &height, const int &volumeSound)
{
  EditEngine	edit(win, save, volumeSound);

  try
    {
      edit.initialize(width, height);
      while (edit.update() == true)
	edit.draw();
      return true;
    }
  catch (const Error &error)
    {
      std::cerr << "Error : " << error.what() << std::endl;
      return true;
    }
  return false;
}
