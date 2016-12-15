//
// Explosion.hpp for bomberman in /home/qu_a/bitbucket/bomberman/inc
// 
// Made by Antoine Qu
// Login   <qu_a@epitech.net>
// 
// Started on  Sun Jun  7 14:16:39 2015 Antoine Qu
// Last update Sat Jun 13 16:25:52 2015 Antoine Qu
//

#ifndef EXPLOSION_HPP_
# define EXPLOSION_HPP_

#include "Geometry.hh"
#include "Texture.hh"
#include "Texture.hpp"
#include "AEntity.hpp"
#include "Map.hpp"

class Explosion : public AEntity
{
  gdl::Texture		tex;
  gdl::Geometry		geometry;
  float			timer;
  const std::string	texPath;

public:
  Explosion(const int, const int, const Entity);
  ~Explosion();

public:
  void			pushUv();
  virtual bool		initGraph();
  virtual void		update(const gdl::Clock &, gdl::Input &, Map *);
  virtual void		drawEntity(gdl::AShader &_shader, const gdl::Clock &);
};

#endif
