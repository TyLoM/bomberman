//
// Thread.hpp for Bomberman in /home/mcnama_d/gitreps/B4-CPP/bomberman/inc
// 
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
// 
// Started on  Sat May  9 16:05:15 2015 Duncan McNAMARA
// Last update Sat May  9 18:04:48 2015 Duncan McNAMARA
//

#ifndef THREAD_HPP_
# define THREAD_HPP_

# include "ScopedLock.hpp"

typedef enum		e_tstatus
  {
    T_NOTSTARTED,
    T_RUNNING,
    T_DEAD
  }			t_status;

class			Thread
{
 public:
  Thread();
  ~Thread();

  void			createThread(const pthread_attr_t *attr,
				     void *(start_routine)(void*),
				     void *arg);
  int			getStatus(void);
  void			joinThread(void **retval);

 public:
  void			setData(void *data);
  void			*getData(void) const;
  
 private:
  void			*data;
  int			status;
  pthread_t		thread;
};

#endif /* !THREAD_HPP_ */
