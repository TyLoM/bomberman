//
// MenuLvls.cpp for qqwe in /home/quentin/bucket/bomberman
//
// Made by Quentin Richard
// Login   <quentin@epitech.net>
//
// Started on  Thu Jun  4 16:03:41 2015 Quentin Richard
// Last update Sun Jun 14 21:51:39 2015 Quentin Richard
//

#include "Menu.hpp"
#include "Process.hpp"
#include "Error.hpp"

void	Menu::checkPlay(const int &x, const int &y)
{
  if ((x >= 373 && y >= 241) && (x <= 643 && y <= 303))
    {
      if (check <= 0)
	{
	  sound->play();
	  tex2.bind();
	  lvl = 1;
	  check = 1;
	  return ;
	}
      return ;
    }
}

bool	Menu::checkExit(const int &x, const int &y)
{
  if ((x >= 375 && y >= 520) && (x <= 649 && y <= 589))
    {
      if (check <= 0)
	{
	  check = 1;
	  sound->play();
	  return false;
	}
    }
  return true;
}

void	Menu::checkOption(const int &x, const int &y)
{
    if ((x >= 376 && y >= 424) && (x <= 646 && y <= 496))
    {
      if (check <= 0)
	{
	  lvl = 5;
	  sound->play();
	  tex6.bind();
	  check = 1;
	  return ;
	}
    }
  return ;
}

void	Menu::checkScore(const int &x, const int &y)
{
  if ((x >= 375 && y >= 332) && (x <= 643 && y <= 400))
    {
      if (check <= 0)
	{
	  sound->play();
	  tex5.bind();
	  lvl = 4;
	  check = 1;
	  return ;
	}
    }
  return ;
}

bool	Menu::mainMenu()
{
  int	x = win->getInput()->getMousePosition().x;
  int	y = win->getInput()->getMousePosition().y;

  checkPlay(x, y);
  checkScore(x, y);
  checkOption(x, y);
  if (checkExit(x, y) == false)
    return false;
  return true;
}

void	Menu::checkNewGame(const int &x, const int &y)
{
  if ((x >= 357 && y >= 208) && (x <= 684 && y <= 277))
    {
      if (check <= 0)
	{
	  lvl = 2;
	  check = 1;
	  sound->play();
	  tex3.bind();
	}
      return ;
    }
}

bool	  Menu::checkLoadGame(const int &x, const int &y)
{
  Process	pro(win, save);

  if ((x >= 359 && y >= 308) && (x <= 681 && y <= 370))
    {
      if (check <= 0)
  	{
	  lvl = 0;
	  check = 1;
	  if (save->fileExist(static_cast<SaveType>(setMap)) == true)
	    {
	      save->setState(true);
	      texLoad.bind();
	      draw();
	      sound->play();
	      music.end();
	      if (pro.goLoad() == false)
		{
		  save->setState(false);
		  return false;
		}
	      music.game();
	      tex.bind();
	      save->setState(false);
	    }
	  else
	    {
	      std::cerr << "There is no save file." << std::endl;
	      save->setState(false);
	    }
  	}
    }
  return true;
}

void	Menu::checkCreateMap(const int &x, const int &y)
{
  if ((x >= 361 && y >= 402) && (x <= 685 && y <= 462))
    {
      if (check <= 0)
	{
	  lvl = 3;
	  check = 1;
	  sound->play();
	  tex4.bind();
	}
      return ;
    }
}


void	Menu::checkReturn(const int &x, const int &y)
{
  if ((x >= 360 && y >= 499) && (x <= 687 && y <= 560))
    {
      if (check <= 0)
	{
	  lvl = 0;
	  check = 1;
	  sound->play();
	  tex.bind();
      	}
      return ;
    }
  return ;
}

bool		Menu::selectMenu()
{
  int		x = win->getInput()->getMousePosition().x;
  int		y = win->getInput()->getMousePosition().y;

  checkNewGame(x, y);
  checkLoadGame(x, y);
  checkCreateMap(x, y);
  checkReturn(x, y);
    return true;
}

bool	Menu::startGame(const int &x, const int &y)
{
  Process	pro(win, save);

  if ((x >= 217 && y >= 495) && (x <= 389 && y <= 568))
    {
      if (check <= 0)
  	{
	  texLoad.bind();
	  draw();
  	  lvl = 0;
  	  check = 1;
	  sound->play();
	  music.end();
	  if (!(pro.goGame(nbPlayer, nbAI, soundGame,
	  		   static_cast<SaveType>(setMap))))
	    return false;
	  music.game();
	  tex.bind();
  	}
    }
  return true;
}

void	Menu::checkGameReturn(const int &x, const int &y)
{
  if ((x >= 660 && y >= 497) && (x <= 833 && y <= 566))
    {
      if (check <= 0)
  	{
  	  lvl = 1;
  	  check = 1;
	  sound->play();
	  tex2.bind();
	  return ;
  	}
    }
}

void	Menu::checkLessPlayer(const int &x, const int &y)
{
  if ((x >= 398 && y >= 196) && (x <= 442 && y <= 229))
    {
      if (check <= 0)
  	{
  	  check = 1;
	  if (nbPlayer > 1)
	    nbPlayer = nbPlayer - 1;
	  std::cout << "nombre de joueur :" << nbPlayer << std::endl;
	  sound->play();
	  return ;
  	}
    }
}

void	Menu::checkMorePlayer(const int &x, const int &y)
{
  if ((x >= 698 && y >= 196) && (x <= 743 && y <= 229))
    {
      if (check <= 0)
  	{
	  //pol->strToScreen("l", glm::vec3(0.53, 0.20 ,0.5));
  	  check = 1;
	  if (nbPlayer < 2)
	    nbPlayer = nbPlayer + 1;
	  std::cout << "nombre de joueur :" << nbPlayer << std::endl;
	  sound->play();
	  return ;
  	}
    }
}

void	Menu::checkMoreAI(const int &x, const int &y)
{
  if ((x >= 700 && y >= 281) && (x <= 746 && y <= 316))
    {
      if (check <= 0)
  	{
  	  check = 1;
	  if (nbAI < 8)
	    nbAI = nbAI + 1;
	  sound->play();
	  std::cout << "nombre de AI :" << nbAI << std::endl;
	  return ;
  	}
    }
}

void	Menu::checkLessAI(const int &x, const int &y)
{
  if ((x >= 398 && y >= 229) && (x <= 442 && y <= 312))
    {
      if (check <= 0)
  	{
  	  check = 1;
	  if (nbAI > 0)
	    nbAI = nbAI - 1;
	  sound->play();
	  std::cout << "nombre de AI :" << nbAI << std::endl;
	  return ;
  	}
    }
}

void	Menu::checkMoreMap(const int &x, const int &y)
{
  if ((x >= 699 && y >= 373) && (x <= 743 && y <= 404))
    {
      if (check <= 0)
  	{
  	  check = 1;
	  if (setMap < 3)
	    setMap = setMap + 1;
	  sound->play();
	  std::cout << "Your map selection :" << nameMap[setMap] << std::endl;
	  return ;
  	}
    }
}

void	Menu::checkLessMap(const int &x, const int &y)
{
  if ((x >= 398 && y >= 372) && (x <= 443 && y <= 404))
    {
      if (check <= 0)
  	{
  	  check = 1;
	  if (setMap > 0)
	    setMap = setMap - 1;
	  sound->play();
	  std::cout << "Your map selection :" <<nameMap[setMap] << std::endl;
	  return ;
  	}
    }
}

bool	Menu::gameMenu()
{
  int		x = win->getInput()->getMousePosition().x;
  int		y = win->getInput()->getMousePosition().y;

  tex3.bind();
  if (startGame(x, y) == false)
    return false;
  checkGameReturn(x, y);
  checkLessPlayer(x, y);
  checkMorePlayer(x , y);
  checkMoreAI(x, y);
  checkLessAI(x, y);
  checkLessMap(x, y);
  checkMoreMap(x, y);
  return true;
}

bool	Menu::startCreateMap(const int &x, const int &y)
{
  Process	pro(win, save);

  if ((x >= 216 && y >= 491) && (x <= 419 && y <= 575))
    {
      if (check <= 0)
  	{
	  lvl = 0;
   	  check = 1;
	  texLoad.bind();
	  draw();
	  sound->play();
	  music.end();
	  if (pro.goCreateMap(widthMap, heightMap, soundCreateMap) == false)
	    return false;
	  music.game();
	  tex.bind();
   	}
    }
  return true;
}

void	Menu::returnMenu(const int &x, const int &y)
{
  if ((x >= 656 && y >= 492) && (x <= 858 && y <= 575))
    {
      if (check <= 0)
  	{
	  lvl = 1;
   	  check = 1;
	  sound->play();
	  tex2.bind();
   	}
    }
  return ;
}

void	Menu::checkHeightMore(const int &x, const int &y)
{
  if ((x >= 699 && y >= 194) && (x <= 743 && y <= 230))
    {
      if (check <= 0)
  	{
   	  check = 1;
	  sound->play();
	  heightMap = heightMap + 1;
	  std::cout << "Height :" << heightMap << std::endl;
   	}
    }
  return ;
}

void	Menu::checkHeightLess(const int &x, const int &y)
{
  if ((x >= 398 && y >= 196) && (x <= 442 && y <= 229))
    {
      if (check <= 0)
  	{
	  if (heightMap > 10)
	    heightMap = heightMap - 1;
   	  check = 1;
	  std::cout << "Height :" << heightMap << std::endl;
	  sound->play();
   	}
    }
  return ;
}

void	Menu::checkWidthMore(const int &x, const int &y)
{
  if ((x >= 698 && y >= 337) && (x <= 742 && y <= 368))
    {
      if (check <= 0)
  	{
   	  check = 1;
	  sound->play();
	  widthMap = widthMap + 1;
	  std::cout << "width :" << widthMap << std::endl;
   	}
    }
  return ;
}

void	Menu::checkWidthLess(const int &x, const int &y)
{
  if ((x >= 398 && y >= 339) && (x <= 441 && y <= 370))
    {
      if (check <= 0)
  	{
	  if (widthMap > 10)
	    widthMap = widthMap - 1;
	  std::cout << "width :" << widthMap << std::endl;
   	  check = 1;
	  sound->play();
   	}
    }
  return ;
}

bool	Menu::createMapMenu()
{
  int		x = win->getInput()->getMousePosition().x;
  int		y = win->getInput()->getMousePosition().y;

  if (startCreateMap(x, y) == false)
    return false;
  returnMenu(x, y);
  checkWidthMore(x, y);
  checkWidthLess(x, y);
  checkHeightMore(x, y);
  checkHeightLess(x, y);
  return true;
}

void	Menu::checkSave(const int &x, const int &y)
{
    if ((x >= 263 && y >= 469) && (x <= 438 && y <= 567))
    {
      if (check <= 0)
  	{
	  lvl = 0;
   	  check = 1;
	  soundGame = soundM;
	  soundCreateMap = soundM;
	  sound->play();
	  std::cout << "in save" <<soundM << std::endl;
	  win->getPtrSound()->setSoundVolume(soundM);
	  music.setVolumeMusic(soundM);
	  tex.bind();
   	}
    }
  return ;

}

void	Menu::checkReturnOption(const int &x, const int &y)
{
  if ((x >= 646 && y >= 495) && (x <= 823 && y <= 567))
    {
      if (check <= 0)
  	{
	  lvl = 0;
   	  check = 1;
	  sound->play();
	  tex.bind();
   	}
    }
  return ;
}

void	Menu::checkMoreSound(const int &x, const int &y)
{
  if ((x >= 699 && y >= 283) && (x <= 742 && y <= 315))
    {
      if (check <= 0)
  	{
   	  check = 1;
	  if (soundM < 100)
	    soundM = soundM + 1;
	  sound->play();
	  std::cout << "sound" << soundM << std::endl;
   	}
    }
  return ;
}

void	Menu::checkLessSound(const int &x, const int &y)
{
  if ((x >= 398 && y >= 281) && (x <= 444 && y <= 314))
    {
      if (check <= 0)
  	{
	  if (soundM > 0)
	    soundM = soundM - 1;
   	  check = 1;
	  sound->play();
	  std::cout << "sound" << soundM << std::endl;
   	}
    }
  return ;
}

bool	Menu::optionMenu()
{
  int		x = win->getInput()->getMousePosition().x;
  int		y = win->getInput()->getMousePosition().y;

  checkSave(x, y);
  checkReturnOption(x, y);
  checkMoreSound(x, y);
  checkLessSound(x, y);
  return true;
}

void	Menu::checkReturnScore(const int &x, const int &y)
{
  if ((x >= 430 && y >= 499) && (x <= 606 && y <= 572))
    {
      if (check <= 0)
  	{
	  lvl = 0;
   	  check = 1;
	  sound->play();
	  tex.bind();
   	}
    }
  return ;
}

bool	Menu::scoreMenu()
{
  int		x = win->getInput()->getMousePosition().x;
  int		y = win->getInput()->getMousePosition().y;

  checkReturnScore(x, y);
  return true;
}

void	Menu::learnFunction(lvlMenu ptr)
{
  selectLvl.push_back(ptr);
}
