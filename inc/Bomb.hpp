//
// Bomb.hpp for qwe in /home/lee_c/gitdepot/bomberman/src
//
// Made by soomin lee
// Login   <lee_c@epitech.net>
//
// Started on  Fri May 22 16:00:46 2015 soomin lee
// Last update Sun Jun 14 09:42:47 2015 Antoine Qu
//

#ifndef BOMB_HPP_
# define BOMB_HPP_

#include "Model.hh"
#include "Map.hpp"
#include "AEntity.hpp"

# define EXPLODE_GET_X ((i == 0) ? (getX()) : (getX() + j))
# define EXPLODE_GET_Y ((i == 0) ? (getY() + j) : (getY()))

/*
** The max range of the bomb will be set depending on the size of the map
*/

class		Bomb : public AEntity
{
  Character	*owner;
  int		range;
  /*
  ** this variable is maybe not necessairy but usefull for bonuses
  */
  unsigned short	clock;

  gdl::Model	model;
  float		timer;
  glm::vec3	vdir;

public:
  Bomb(const int, const int, Character *, const int, const Entity type = BOMB);
  ~Bomb();

public:
  Character		*getOwner(void) const;
  unsigned int		getRange(void) const;
  unsigned short	getClock(void) const;

public:
  void			setTimer(float);

public:
  virtual bool		initGraph(void);
  virtual void		update(const gdl::Clock &_clock, gdl::Input &_input,
			       Map *);
  virtual void		drawEntity(gdl::AShader &_Shader, const gdl::Clock &_clock);

public:
  void			detonate(Map *) const;
  void			directDetonate(Map *, const int, const int) const;
  void			explode(Map *, const int, const int) const;
  void			destroyThis(Map *, const int, const int, const Entity) const;
};

#endif
