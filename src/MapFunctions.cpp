//
// MapFunctions.cpp for qwe in /home/lee_c/gitdepot/bomberman
//
// Made by soomin lee
// Login   <lee_c@epitech.net>
//
// Started on  Thu May 28 16:06:25 2015 soomin lee
// Last update Sun Jun 14 21:38:53 2015 Antoine Qu
//

#include <cstdlib>
#include "Map.hpp"
#include "Bonus.hpp"

void	Map::generateBlocks(const int howMany, const Entity type)
{
  for (int blocks = 0; blocks <= howMany; ++blocks)
    {
      int x = rand() % width + 1;
      int y = rand() % height + 1;

      if (checkElement(x, y, BLOCK) == false
	  && checkElement(x, y, WALL) == false
	  && checkElement(x, y, PLAYER) == false)
	addElement(x, y, new Box(x, y, skin, type));
    }
}

void	Map::generatePresetA(void)
{
  for (int y = 0; y < height + 2; ++y)
    for (int x = 0; x < width + 2; ++x)
      if (y != 0 && x % 2 == 0 && y != height + 1
	  && x != 0 && x != width + 1 && y % 2 == 0)
	addElement(x, y, new Box(x, y, skin, WALL));
}

void	Map::generatePresetB(void)
{
}

void	Map::generateCustom(void)
{
  for (int y = 1; y < height + 1; ++y)
    for (int x = 1; x < width + 1; ++x)
      {
	addElement(x, y, new Box(x, y, skin, VOID_BLOCK));
      }
}

void	Map::generateLoad(void)
{
}

void	Map::generateRandom(void)
{
  int	howManyLeft = (width * height) / 10;
  int	howManyGene = (width * height) - howManyLeft;

  generateBlocks((howManyGene / 10), WALL);
  generateBlocks((howManyGene - (howManyGene / 10)), BLOCK);
}
