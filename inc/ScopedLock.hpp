//
// ScopedLock.hpp for Bomberman in /home/mcnama_d/gitreps/B4-CPP/bomberman/inc
// 
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
// 
// Started on  Sat May  9 16:05:02 2015 Duncan McNAMARA
// Last update Sat May  9 18:05:36 2015 Duncan McNAMARA
//

#ifndef SCOPEDLOCK_HPP_
# define SCOPEDLOCK_HPP_

#include "Mutex.hpp"

class			ScopedLock
{
public:
  ScopedLock(Mutex *m);
  ~ScopedLock();
private:
  Mutex			*m;
};

#endif /* SCOPEDLOCK_HPP_ */
