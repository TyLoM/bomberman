

#ifndef _WORKER_HH_
#define  _WORKER_HH_

#include "Mutex.hpp"
#include "CondVar.hpp"
#include "Thread.hpp"
#include <iostream>
#include <vector>

class Worker
{
  Thread			*thread;
  Mutex				&mutex;
  CondVar			&cond;
  int				nbTask;
  bool				busy;
  bool				end;
  std::vector<void(Worker:: *)(void)>	tasks;	
  
public:
  Worker(Mutex &, CondVar &);
  ~Worker();
public:
  void	task1();
  void	task2();
  void  start();
  void  setThread(Thread *t);
  void  setEnd(bool);
  bool  getStatus() const;
};

#endif
