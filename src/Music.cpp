//
// Music.cpp for Bomberman in /home/mcnama_d/gitreps/B4-CPP/bomberman/src
//
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
//
// Started on  Sat Jun  6 11:17:53 2015 Duncan McNAMARA
// Last update Sun Jun 14 21:39:57 2015 Antoine Qu
//

#include <iostream>
#include "Music.hpp"

Music::Music()
{
}

Music::~Music()
{
  music.stop();
}

void	Music::init(musicType type)
{
  if (type == MSC_GAME)
    {
      data.push_back("./assets/music/SW-Top_of_the_world_2.wav");
      data.push_back("./assets/music/Tobu-Higher.wav");
      data.push_back("./assets/music/Tobu-Hope_Original_Mix_.wav");
      data.push_back("./assets/music/TheFatRat-Time.wav");
    }
  else if (type == MSC_EDITOR)
    data.push_back("./assets/music/Melokind_-_Fr_hlingsgef_hle_Original_Mix_by_Meloki.wav");
  else
    data.push_back("./assets/music/Tobu-Candyland.wav");
}

bool	Music::game()
{
  if (!music.openFromFile(data[rand() % data.size()]))
    {
      std::cerr << "Failed to load music" << std::endl;
      return (false);
    }
  music.setVolume(50);
  music.setLoop(true);
  music.play();
  return (false);
}

void	Music::setVolumeMusic(const int &volume)
{
  music.setVolume(volume);
}

bool	Music::end()
{
  music.setLoop(false);
  music.stop();
  return (true);
}
