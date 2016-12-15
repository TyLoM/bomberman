//
// Texture.cpp for bomberman in /home/qu_a/bitbucket/bomberman/src
// 
// Made by Antoine Qu
// Login   <qu_a@epitech.net>
// 
// Started on  Mon Jun  1 15:35:07 2015 Antoine Qu
// Last update Sun Jun 14 21:09:27 2015 Duncan McNAMARA
//

#include "Texture.hpp"
#include <string>

Texture::Texture()
{
}

Texture::~Texture()
{
}

void		Texture::initialize()
{
  texture.insert(std::pair<Entity, const std::string>(POWERUP, tex_powerup));
  texture.insert(std::pair<Entity, const std::string>(BOMBUP, tex_bombup));
  texture.insert(std::pair<Entity, const std::string>(SPEEDUP, tex_speedup));
  texture.insert(std::pair<Entity, const std::string>(VOID_BLOCK, tex_voidblock));
  texture.insert(std::pair<Entity, const std::string>(BLOCK, tex_block));
  texture.insert(std::pair<Entity, const std::string>(WALL, tex_wall));
  texture.insert(std::pair<Entity, const std::string>(EXPLOSION, tex_explosion));
  texture.insert(std::pair<Entity, const std::string>(CURSOR1, tex_cursred));
  texture.insert(std::pair<Entity, const std::string>(CURSOR2, tex_cursblue));
  texture.insert(std::pair<Entity, const std::string>(GROUND, tex_ground));
  texture.insert(std::pair<Entity, const std::string>(BACKGROUND, tex_background));
  texture.insert(std::pair<Entity, const std::string>(YOUWIN, tex_youwin));
  texture.insert(std::pair<Entity, const std::string>(YOULOSE, tex_youlose));
}

const std::string	&Texture::getPath(const Entity _path)
{
  return (texture[_path]);
}
