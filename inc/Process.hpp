//
// Process.hpp for qwe in /home/quentin/bucket/bomberman
//
// Made by Quentin Richard
// Login   <quentin@epitech.net>
//
// Started on  Tue Jun  2 12:51:02 2015 Quentin Richard
// Last update Sun Jun 14 16:36:09 2015 Quentin Richard
//

#ifndef PROCESS_H_
#define PROCESS_H_

# include "Game.hh"
# include "GraphEngine.hpp"
# include "Menu.hpp"
# include "AEntity.hpp"

class	Process
{
public:
  Process(GraphEngine *, Save *);
  ~Process();

public:
  bool	goMenu(AEntity *pol);
  bool	goGame(const int &, const int &, const int &, const SaveType &); // temporairement un bool le temps que le menu sois fini.
  bool	goLoad(); // temporairement un bool le temps que le menu sois fini.
  bool	goCreateMap(const int &, const int &, const int &);

private:
  GraphEngine	*win;
  Save		*save;
};


#endif
