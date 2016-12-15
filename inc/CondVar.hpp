//
// CondVar.hpp for bomberman in /home/mcnama_d/gitreps/B4-CPP/bomberman/inc
// 
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
// 
// Started on  Sat May  9 15:59:40 2015 Duncan McNAMARA
// Last update Sat May  9 18:04:29 2015 Duncan McNAMARA
//

#ifndef CONDVAR_HPP_
# define CONDVAR_HPP_

# include <pthread.h>
# include "Mutex.hpp"

class			CondVar
{
public:
  CondVar();
  ~CondVar();
  void			wait(Mutex *m);
  void			signal(void);
  void			broadcast(void);
  void			setMutex(Mutex *m);
private:
  pthread_cond_t	cond;
};

#endif /* !ICONDVAR_HPP_ */
