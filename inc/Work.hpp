//
// Work.hpp for lol in /home/tylo/rendu/bomberman
//
// Made by TyLo
// Login   <tylo@epitech.net>
//
// Started on  Wed Jun  3 17:03:44 2015 TyLo
// Last update Wed Jun  3 17:24:36 2015 TyLo
//

#ifndef _WORK_HH_
#define _WORK_HH_

class Work
{
  typedef void* (*Fct)(void *);
public:
  Work(Fct, void *arg);
  ~Work();
  void start();
private:
  void *(*fct)(void *);
  void *m_arg;
};

#endif
