//
// Box.hpp for bomberman in /home/qu_a/bitbucket/bomberman/inc
//
// Made by Antoine Qu
// Login   <qu_a@epitech.net>
//
// Started on  Fri May 22 16:02:01 2015 Antoine Qu
// Last update Sun Jun 14 01:21:40 2015 Duncan McNAMARA
//

#ifndef BOX_HPP_
# define BOX_HPP_

#include "Geometry.hh"
#include "Texture.hh"
#include "AEntity.hpp"
#include "Texture.hpp"

class		Box : public AEntity
{
private:
  gdl::Texture		tex;
  gdl::Geometry		geometry;
  const std::string	&texPath;

public:
  Box(const int x, const int y, Texture *_skin, const Entity type = WALL);
  ~Box();

public:
  void		pushUv();
  virtual bool	initGraph();
  virtual void	update(const gdl::Clock &_clock, gdl::Input &_input,
		       Map *board);
  virtual void	drawEntity(gdl::AShader &_shader, const gdl::Clock &);
public:
  void		changeToCursor();
};

#endif	// !BOX_HPP_
