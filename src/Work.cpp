//
// Work.cpp for lol in /home/tylo/rendu/bomberman/inc
//
// Made by TyLo
// Login   <tylo@epitech.net>
//
// Started on  Wed Jun  3 17:17:25 2015 TyLo
// Last update Sun Jun 14 21:46:26 2015 Antoine Qu
//

#include "Work.hpp"

Work::Work(Fct _fct, void *arg)
{
  this->fct = _fct;
  this->m_arg = arg;
}

Work::~Work()
{
}

void	Work::start()
{
  (fct)(m_arg);
}
