//
// Texture.hpp for bomberman in /home/qu_a/bitbucket/bomberman/inc
// 
// Made by Antoine Qu
// Login   <qu_a@epitech.net>
// 
// Started on  Mon Jun  1 15:00:52 2015 Antoine Qu
// Last update Sun Jun 14 21:08:28 2015 Duncan McNAMARA
//

#ifndef	TEXTURE_HPP_
# define TEXTURE_HPP_

#include "AEntity.hpp"
#include <map>

static const std::string	tex_powerup = "./assets/Bonus/flamme.tga";
static const std::string	tex_bombup = "./assets/Bonus/bombe.tga";
static const std::string	tex_speedup = "./assets/Bonus/speed.tga";
static const std::string	tex_voidblock = "./assets/Box/Bluebox.tga";
static const std::string	tex_block = "./assets/Box/Orangebox.tga";
static const std::string	tex_wall = "./assets/Box/Violetbox.tga";
static const std::string	tex_explosion = "./assets/Explosion/Explosion.tga";
static const std::string	tex_cursred = "./assets/Box/Redbox.tga";
static const std::string	tex_cursblue = "./assets/Box/Bluebox.tga";
static const std::string	tex_ground = "./assets/Box/texMap.tga";
static const std::string	tex_background = "./assets/prototypes/space_background.tga";
static const std::string	tex_youwin = "./assets/prototypes/YouWin.tga";
static const std::string	tex_youlose = "./assets/prototypes/YouLose.tga";

class Texture
{
private:
  std::map<const Entity, const std::string>	texture;

public:
  Texture();
  ~Texture();

public:
  void	initialize();
  const std::string &getPath(const Entity);
};

#endif
