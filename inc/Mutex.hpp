//
// Mutex.hpp for Bomberman in /home/mcnama_d/gitreps/B4-CPP/bomberman/inc
// 
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
// 
// Started on  Sat May  9 16:04:15 2015 Duncan McNAMARA
// Last update Sat May  9 18:06:11 2015 Duncan McNAMARA
//

#ifndef MUTEX_HPP_
# define MUTEX_HPP_

# include <pthread.h>

class			Mutex
{
 public:
  Mutex();
  ~Mutex();
  void			lock(void);
  void			unlock(void);
  bool			trylock(void);

  pthread_mutex_t	*getMutex(void);
private:
  pthread_mutex_t	m;
};

#endif /* MUTEX_HPP_ */
