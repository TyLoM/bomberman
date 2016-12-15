//
// CondVar.cpp for bomberman in /home/mcnama_d/gitreps/B4-CPP/bomberman/src
// 
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
// 
// Started on  Sat May  9 16:00:48 2015 Duncan McNAMARA
// Last update Mon May 11 13:28:58 2015 Duncan McNAMARA
//

#include "CondVar.hpp"

CondVar::CondVar()
{
  pthread_cond_init(&this->cond, NULL);
}

CondVar::~CondVar()
{
  pthread_cond_destroy(&this->cond);
}

void			CondVar::wait(Mutex *m)
{
  pthread_cond_wait(&this->cond, m->getMutex());
}

void			CondVar::signal()
{
  pthread_cond_signal(&this->cond);
}

void			CondVar::broadcast()
{
  pthread_cond_broadcast(&this->cond);
}
