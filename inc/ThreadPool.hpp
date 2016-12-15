//
// ThreadPool.hpp for lol in /home/tylo/rendu/bomberman
//
// Made by TyLo
// Login   <tylo@epitech.net>
//
// Started on  Wed Jun  3 17:20:16 2015 TyLo
// Last update Thu Jun  4 17:05:01 2015 TyLo
//


#ifndef _THREADPOOL_HH_
#define  _THREADPOOL_HH_

#include "Mutex.hpp"
#include "CondVar.hpp"
#include "Thread.hpp"
#include <iostream>
#include <vector>
#include "Work.hpp"
#include <deque>

class ThreadPool
{
public:
  ThreadPool();
  ThreadPool(unsigned int size);
  ~ThreadPool();
public:
  void	CommandCenter(); //mb const
  void	addWork(Work *work);
  void	destroyThreadPool();
public:
  int	getSize() const;
private:
  unsigned int	size;
  std::vector<Thread *> threads;
  std::deque<Work *>	works;
  Mutex			m;
  CondVar		cond;
};

void	*start(void *void_threadpool);
#endif
