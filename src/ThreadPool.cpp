//
// ThreadPool.cpp for lol in /home/tylo/rendu/bomberman
//
// Made by TyLo
// Login   <tylo@epitech.net>
//
// Started on  Wed Jun  3 15:59:59 2015 TyLo
// Last update Sun Jun 14 21:46:44 2015 Antoine Qu
//

#include "ThreadPool.hpp"

ThreadPool::ThreadPool()
{
}

ThreadPool::ThreadPool(unsigned int nb)
{
  this->size = nb;
  for (; nb != 0; --nb)
    {
      Thread *tmp = new Thread;
      tmp->createThread(NULL, start, this);
      threads.push_back(tmp);
    }
}

ThreadPool::~ThreadPool()
{
}

int	ThreadPool::getSize() const
{
  return (this->size);
}

void	ThreadPool::destroyThreadPool()
{

}

void	ThreadPool::CommandCenter()
{
  Work	*work = NULL;
  while (true)
    {
      m.lock();
      if (works.size() == 0)
	{
	  cond.wait(&m);
	  m.unlock();
	}
      else
	{
	  work = works.front();
	  works.pop_front();
	  m.unlock();
	  delete work;
	}
    }
}

void	ThreadPool::addWork(Work *work)
{
  m.lock();
  works.push_back(work);
  cond.signal();
  m.unlock();
}

void	*start(void *void_threadpool)
{
  ThreadPool *tmp = (ThreadPool *)void_threadpool;
  tmp->CommandCenter();
  return (NULL);
}
