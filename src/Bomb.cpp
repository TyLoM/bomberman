//
// Bomb.cpp for qwe in /home/lee_c/gitdepot/bomberman/src
//
// Made by soomin lee
// Login   <lee_c@epitech.net>
//
// Started on  Fri May 22 16:48:44 2015 soomin lee
// Last update Sun Jun 14 21:23:47 2015 Antoine Qu
//

#include "Bomb.hpp"
#include "Error.hpp"
#include "Explosion.hpp"

Bomb::Bomb(const int _x, const int _y, Character *_owner, const int _playerPower, const Entity _type)
  : AEntity(_x, _y, _type), owner(_owner), range(_playerPower)
{
}

Bomb::~Bomb()
{
}

Character	*Bomb::getOwner(void) const
{
  return owner;
}

unsigned int	Bomb::getRange(void) const
{
  return range;
}

unsigned short	Bomb::getClock(void) const
{
  return clock;
}

bool		Bomb::initGraph(void)
{
  pos += glm::vec3(0, 0, -0.5);
  rot += glm::vec3(90, 0, 0);
  scale *= glm::vec3(0.06, 0.06, 0.06);
  if (!model.load("./assets/Bomb/Bomb.fbx"))
    throw Error("Failed to load the bomb model");
  timer = 0.0;
  return true;
}

void		Bomb::update(const gdl::Clock &_clock, gdl::Input &, Map *board)
{
  timer += _clock.getElapsed();
  if (timer >= 2.0)
    detonate(board);
  scale *= glm::vec3(1.002, 1.002, 1.002);
}

void		Bomb::setTimer(float value)
{
  timer = value;
}

void		Bomb::drawEntity(gdl::AShader &_shader, const gdl::Clock &_clock)
{
  model.draw(_shader, getTransformation(), _clock.getElapsed());
}

void	    	Bomb::detonate(Map *board) const
{
  explode(board, getX(), getY());
  directDetonate(board, 0, 1);
  directDetonate(board, 1, 0);
  directDetonate(board, 0, -1);
  directDetonate(board, -1, 0);
  if (owner != NULL)
    owner->incCurBomb();
  board->deleteElement(getX(), getY(), getId());
}

void		Bomb::directDetonate(Map *board, const int dX, const int dY) const
{
  int		i;

  i = 1;
  while (i <= range
	 && board->checkElement(getX() + (i * dX), getY() + (i * dY), WALL) == false
	 && board->checkElement(getX() + (i * dX), getY() + (i * dY), BLOCK) == false)
    {
      explode(board, getX() + (i * dX), getY() + (i * dY));
      ++i;
    }
  if (i <= range && board->checkElement(getX() + (i * dX), getY() + (i * dY), BLOCK))
    explode(board, getX() + (i * dX), getY() + (i * dY));
}

void		Bomb::explode(Map *board, const int x, const int y) const
{
  bool		bonusProtected = false;

  while (board->checkElement(x, y, PLAYER))
    destroyThis(board, x, y, PLAYER);
  if (board->checkElement(x, y, BLOCK))
    {
      bonusProtected = true;
      destroyThis(board, x, y, BLOCK);
    }
  else if (board->checkElement(x, y, BOMB) && !(x == getX() && y == getY()))
    destroyThis(board, x, y, BOMB);
  for (int bonusEntity = POWERUP; !bonusProtected && bonusEntity < ENB; ++bonusEntity)
    {
      if (board->checkElement(x, y, static_cast<Entity>(bonusEntity)))
	destroyThis(board, x, y, static_cast<Entity>(bonusEntity));
    }
  if (board->checkElement(x, y, EXPLOSION) == false)
    board->addElement(x, y, new Explosion(x, y, EXPLOSION));
}

void					Bomb::destroyThis(Map *board, const int x, const int y, const Entity type) const
{
  bool					destroyed = false;
  std::vector<AEntity *>		*elemList;

  elemList = board->getVecEntityAt(x, y);
  for (std::vector<AEntity *>::iterator	it = elemList->begin();
       !destroyed && it != elemList->end(); ++it)
    {
      if (type == BOMB)
      	(static_cast<Bomb *>(*it))->setTimer(2.0);
      else if ((*it)->getType() == type)
      	{
	  board->deleteElement(x, y, (*it)->getId());
	  destroyed = true;
	}
    }
}
