//
// Bonus.hpp for bomberman in /home/qu_a/bitbucket/bomberman/inc
//
// Made by Antoine Qu
// Login   <qu_a@epitech.net>
//
// Started on  Sat May 23 16:51:55 2015 Antoine Qu
// Last update Sun Jun  7 16:00:49 2015 Antoine Qu
//

#ifndef BONUS_HPP_
# define BONUS_HPP_

#include "Geometry.hh"
#include "Texture.hh"
#include "Texture.hpp"
#include "AEntity.hpp"
#include <map>

class Bonus : public AEntity
{
private:
  gdl::Texture		tex;
  gdl::Geometry		geometry;
  const std::string	&texPath;

private:
  Bonus(const Bonus &);
  Bonus	&operator=(const Bonus &);

public:
  Bonus(const int x, const int y, Texture *texture, const Entity type = POWERUP);
  ~Bonus();

public:
  Entity	getType() const;

public:
  void		pushUv();
  virtual bool	initGraph();
  virtual void	update(const gdl::Clock &, gdl::Input &, Map *);
  virtual void	drawEntity(gdl::AShader &_shader, const gdl::Clock &);
};

#endif	// !BONUS_HPP_
