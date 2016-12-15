//
// main.cpp for qew in /Users/Omera/bucket/Bomberman/src
//
// Made by Quentin Richard
// Login   <Omera@epitech.net>
//
// Started on  Mon May  4 18:28:45 2015 Quentin Richard
// Last update Sun Jun 14 22:43:37 2015 david tang
//

#include <iostream>
#include "Error.hpp"
#include "Process.hpp"
#include "Police.hpp"

int			main()
{
  try
    {
      GraphEngine	win;
      Save		*save = new Save;
      Process		pro(&win, save);
      AEntity		*pol = new Police(&win);

      win.initialize();
      pol->initGraph();
      save->setState(false);
      pro.goMenu(pol);
      delete pol;
      delete save;
    }
  catch (std::runtime_error &e)
    {
      std::cerr << e.what() << std::endl;
      return 1;
    }
  return 0;
}
