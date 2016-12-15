//
// Sound.cpp for Bomberman in /home/mcnama_d/gitreps/B4-CPP/bomberman/src
//
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
//
// Started on  Sat Jun  6 11:56:19 2015 Duncan McNAMARA
// Last update Sun Jun 14 21:40:57 2015 Antoine Qu
//

#include "Sound.hpp"

Sound::Sound()
{
}

Sound::~Sound()
{
}

bool	Sound::init()
{
  sound[SDMENU] = new sf::Music;
  if (!sound[SDMENU]->openFromFile("./assets/sounds/sdmenu.wav"))
    return (false);
  sound[SDSTART] = new sf::Music;
  if (!sound[SDSTART]->openFromFile("./assets/sounds/sdstart.wav"))
    return (false);
  sound[SDGAMEOVER] = new sf::Music;
  if (!sound[SDGAMEOVER]->openFromFile("./assets/sounds/sdgameover.wav"))
    return (false);
  sound[SDBOMB] = new sf::Music;
  if (!sound[SDBOMB]->openFromFile("./assets/sounds/sdbomb.wav"))
    return (false);
  return (true);
}

sf::Music	*Sound::getSound(Sounds id)
{
  return (sound[id]);
}

void	Sound::setSoundVolume(const int &volume)
{
  sound[SDBOMB]->setVolume(volume);
  sound[SDMENU]->setVolume(volume);
  sound[SDSTART]->setVolume(volume);
  sound[SDGAMEOVER]->setVolume(volume);
}
