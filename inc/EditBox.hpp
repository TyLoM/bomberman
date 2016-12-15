//
// EditBox.hpp for Bomberman in /home/mcnama_d/gitreps/B4-CPP/bomberman/inc
// 
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
// 
// Started on  Tue Jun  9 16:14:35 2015 Duncan McNAMARA
// Last update Sun Jun 14 22:39:31 2015 david tang
//

#ifndef EDITBOX_HPP_
# define EDITBOX_HPP_

#include "Geometry.hh"
#include "Texture.hh"
#include "AEntity.hpp"
#include "Texture.hpp"
#include "Map.hpp"

class				EditBox
{
  typedef void  (EditBox::*mvFctBox)(const Map *board);

private:
  std::vector<AEntity*>		blocks;
  Texture			*skin;
  int				texType;
  AEntity			*box;
  std::map<int, mvFctBox>	mvFcts;
public:
  EditBox(Texture *_skin);
  ~EditBox();

public:
  bool				initialize(void);
  void				update(const gdl::Clock &_clock, gdl::Input &_input,
				       Map *board);
  void				draw(gdl::AShader &_shader, const gdl::Clock &_clock);

public:
  glm::vec3			getPos(void);

public:
  void				placeBlock(gdl::Input &input, Map *board);
  void				moveLeft(const Map *);
  void				moveRight(const Map *board);
  void				moveUp(const Map *board);
  void				moveDown(const Map *);
  void				nextTex(void);
  void				prevTex(void);
};

#endif
