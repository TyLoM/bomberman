//
// ScopedLock.cpp for Bomberman in /home/mcnama_d/gitreps/B4-CPP/bomberman/src
// 
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
// 
// Started on  Sat May  9 15:50:45 2015 Duncan McNAMARA
// Last update Sat May  9 18:07:07 2015 Duncan McNAMARA
//

#include "ScopedLock.hpp"

ScopedLock::ScopedLock(Mutex *m)
{
  this->m = m;
  this->m->lock();
}

ScopedLock::~ScopedLock()
{
  this->m->unlock();
}
