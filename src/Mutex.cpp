//
// Mutex.cpp for Bomberman in /home/mcnama_d/gitreps/B4-CPP/bomberman/src
// 
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
// 
// Started on  Sat May  9 15:50:33 2015 Duncan McNAMARA
// Last update Sat May  9 15:50:34 2015 Duncan McNAMARA
//

#include "Mutex.hpp"

Mutex::Mutex()
{
  pthread_mutex_init(&this->m, NULL);
}

Mutex::~Mutex() {}

void	Mutex::lock()
{
  pthread_mutex_lock(&this->m);
}

void	Mutex::unlock()
{
  pthread_mutex_unlock(&this->m);
}

bool	Mutex::trylock()
{
  if (!pthread_mutex_trylock(&this->m))
    return (true);
  return (false);
}

pthread_mutex_t		*Mutex::getMutex(void)
{
  return (&this->m);
}
