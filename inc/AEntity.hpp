//
// AEntity.hpp for qwe in /home/lee_c/gitdepot/bomberman/src
//
// Made by soomin lee
// Login   <lee_c@epitech.net>
//
// Started on  Fri May 22 15:41:17 2015 soomin lee
// Last update Sun Jun 14 21:06:33 2015 Duncan McNAMARA
//

#ifndef AENTITY_HPP_
# define AENTITY_HPP_

# include "SdlContext.hh"
# include "Clock.hh"
# include "BasicShader.hh"

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

/*
** This enum is a list of all the possible entities in the game
** Some entities like items will be added later on
*/

# define DEFAULT_POWER	2
# define DEFAULT_SPEED	1
# define DEFAULT_MBOMB	1
# define DEFAULT_TEAM	1

class		Map;

enum		Entity
  {
    PLAYER,
    VOID_BLOCK,
    BLOCK,
    WALL,
    CURSOR1,
    CURSOR2,
    BACKGROUND,
    GROUND,
    YOUWIN,
    YOULOSE,
    EXPLOSION,
    BOMB,
    POWERUP,
    SPEEDUP,
    BOMBUP,
    ENB
  };

class		AEntity
{
protected:
  int		id;
  Entity	type;

  glm::vec3	pos;
  glm::vec3	rot;
  glm::vec3	scale;

public:
  AEntity(const int, const int, const Entity type = ENB, const int id = -1);
  virtual ~AEntity();

public:
  int		getX(void)	const;
  int		getY(void)	const;
  int		getId(void)	const;
  Entity	getType(void)	const;
  glm::vec3	getPos(void)	const;

public:
  void		setId(const int);

public:
  virtual bool	initGraph(void) = 0;
  virtual void	update(const gdl::Clock &_clock, gdl::Input &_input,
		       Map *board) = 0;
  virtual void	drawEntity(gdl::AShader &_Shader, const gdl::Clock &_clock) = 0;

public:
  void		ftranslate(const glm::vec3 &_v);
  void		frotate(const glm::vec3 &_axis, const float _angle);
  void		fscale(const glm::vec3 &_scale);
  glm::mat4	getTransformation(void) const;
};

#endif
