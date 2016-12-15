//
// Music.hpp for Bomberman in /home/mcnama_d/gitreps/B4-CPP/bomberman/src
//
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
//
// Started on  Sat Jun  6 11:00:38 2015 Duncan McNAMARA
// Last update Sat Jun 13 18:39:50 2015 Quentin Richard
//

#ifndef MUSIC_HPP_
# define MUSIC_HPP_

# include <SFML/Audio.hpp>
# include <vector>

enum		musicType
  {
    MSC_MENU,
    MSC_GAME,
    MSC_EDITOR
  };
class				Music
{
private:
  sf::Music			music;
  std::vector<std::string>	data;

public:
  Music();
  ~Music();

public:
  void		init(musicType type);
  bool		game();
  bool		end();
  void		setVolumeMusic(const int &);

};

#endif /* !MUSIC_HPP_ */
