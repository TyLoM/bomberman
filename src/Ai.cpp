//
// Ai.cpp for  in /home/tang_i/bucket/bomberman
// 
// Made by david tang
// Login   <tang_i@epitech.net>
// 
// Started on  Fri Jun 12 10:28:11 2015 david tang
// Last update Sat Jun 13 15:06:54 2015 david tang
//

#include "Character.hpp"
#include "Error.hpp"
#include "Bomb.hpp"
#include <vector>
#include <cmath>

bool	Character::moveAway(Map *testmap, std::pair<int, int> &coord)
{
  if (coord.first == getX())
    {
      if (testmap->checkCharMove((getX() - 1), getY()))
	std::cout << "move right" << std::endl;
      else if (testmap->checkCharMove((getX() + 1), getY()))
	std::cout << "move left" << std::endl;
      else
	{
	  if (coord.second > getY())
	    std::cout << "move down" << std::endl;
	  else
	    std::cout << "move up" << std::endl;
	}
    }
  else
    {
      if (testmap->checkCharMove(getX(), (getY() + 1)))
	std::cout << "move up" << std::endl;
      else if (testmap->checkCharMove(getX(), (getY() - 1)))
	std::cout << "move down" << std::endl;
      else
	{
	  if (coord.first > getX())
	    std::cout << "move left" << std::endl;
	  else
	    std::cout << "move right" << std::endl;
	}
    }
  return (false);
}

bool		Character::checkBomb(Map *testmap, std::pair<int, int> &coord, unsigned int limit)
{
  int	min = getX();
  int	max = getX();

  (min = min - limit) <= 1 ? min : (min = 1);
  (max = max + limit) > testmap->getWidth() ? (max = testmap->getWidth()) : max;
  for (int x = min; x < max; ++x)
    if (testmap->checkElement(x, getY(), BOMB))
      {
	coord.first = x;
	coord.second = getY();
	return true;
      }
  (min = getY() - limit) <= 1 ? min : (min = 1);
  (max = getY() + limit) > testmap->getHeight() ? (max = testmap->getHeight()) : max;
  for (int y = min; y < max; ++y)
    if (testmap->checkElement(getX(), y, BOMB))
      {
	coord.first = getX();
	coord.second = y;
	return true;
      }
  return false;
}

bool				Character::checkAround(Map *testmap, std::pair<int, int> &coord, unsigned int limit)
{
  std::vector<AEntity *>	**board = testmap->getBoard();
  int				xmin = getX();
  int				ymin = getY();
  int				xmax = getX();
  int				ymax = getY();

  (xmin = xmin - limit) <= 1 ? xmin : (xmin = 1);
  (xmax = xmax + limit) > testmap->getWidth() ? (xmax = testmap->getWidth()) : xmax;
  (ymin = ymin - limit) <= 1 ? ymin : (ymin = 1);
  (ymax = ymax + limit) > testmap->getHeight() ? (ymax = testmap->getHeight()) : ymax;
  for (int y = ymin; y < ymax + 1; ++y)
    for (int x = xmin; x < xmax + 1; ++x)
      for (std::vector<AEntity *>::iterator ite  = board[y][x].begin(); ite != board[y][x].end(); ++ite)
	{
	  if ((*ite)->getType() == POWERUP || (*ite)->getType() == SPEEDUP ||
	      (*ite)->getType() == BOMBUP || (*ite)->getType() == BLOCK)
	    {
	      coord.first = x;
	      coord.second = y;
	      return true;
	    }
	}
  return false;
}

bool	Character::getItem()
{
  return false;
}

bool	Character::moveOver()
{
  return false;
}

bool	Character::searchItem(Map *testmap, std::pair<int, int> &coord)
{
  if (checkAround(testmap, coord, 3))
    getItem();
  else
    moveOver();
  return false;
}

bool			Character::moveAi(const gdl::Clock &, Map *board)
{
  (void) clock;
  std::pair<int, int>	coord(-1, -1);

  if (checkBomb(board, coord, 2))
    moveAway(board, coord);
  else
    searchItem(board, coord);
  return true;
}
