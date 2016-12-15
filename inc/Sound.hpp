//
// Sound.hpp for Bomberman in /home/mcnama_d/gitreps/B4-CPP/bomberman/src
//
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
//
// Started on  Sat Jun  6 11:56:12 2015 Duncan McNAMARA
// Last update Sat Jun 13 19:07:27 2015 Quentin Richard
//

#ifndef SOUND_HPP_
# define SOUND_HPP_

# include <map>
# include <SFML/Audio.hpp>
# include "AEntity.hpp"

enum	Sounds
  {
    SDMENU,
    SDSTART,
    SDGAMEOVER,
    SDVICTORY,
    SDBOMB,
    SDPOWERUP,
    SDSPEEDUP,
    SDBOMBUP,
    SDENB,
  };

class				Sound
{
private:
  std::map<Sounds, sf::Music*>	sound;

public:
  Sound();
  ~Sound();

public:
  bool				init();
  sf::Music			*getSound(Sounds id);
  void				setSoundVolume(const int &);
};

#endif /* SOUND_HPP_ */
