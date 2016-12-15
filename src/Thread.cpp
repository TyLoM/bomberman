//
// Thread.cpp for Bomberman in /home/mcnama_d/gitreps/B4-CPP/bomberman/src
// 
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
// 
// Started on  Sat May  9 15:50:58 2015 Duncan McNAMARA
// Last update Sun Jun 14 21:41:46 2015 Antoine Qu
//

#include "Thread.hpp"
#include "Error.hpp"

Thread::Thread()
{
  this->status = T_NOTSTARTED;
}

Thread::~Thread()
{
}

void		Thread::createThread(const pthread_attr_t *attr,
				     void *(start_routine)(void*),
				     void *arg)
{
  if (this->status > T_NOTSTARTED)
    throw Error("ERR_THREADSTARTD");
  if (pthread_create(&this->thread, attr, start_routine, arg) != 0)
    throw Error("ERR_THREADCREATE");
  this->status = T_RUNNING;
}

int		Thread::getStatus(void)
{
  return (this->status);
}

void		Thread::joinThread(void **retval)
{
  if (pthread_join(this->thread, retval) != 0)
    throw Error("ERR_THREAD_JOIN_");
  this->status = T_DEAD;
}

void		Thread::setData(void *Data)
{
  this->data = Data;
}

void		*Thread::getData(void) const
{
  return (data);
}
