//
// Map.cpp for lol in /home/tylo/rendu/bomberman
//
// Made by TyLo
// Login   <tylo@epitech.net>
//
// Started on  Sat Jun 13 01:33:12 2015 TyLo
// Last update Sun Jun 14 23:10:27 2015 Duncan McNAMARA
//

#include "Map.hpp"
#include <iostream>
#include <algorithm>

//to move into Map.hpp
#include "Bonus.hpp"
#include "Bomb.hpp"
#include "Explosion.hpp"

Map::Map(const int _width, const int _height, Texture *_skin)
  : skin(_skin), width(_width), height(_height), idCount(0), nbPlayer(1), nbAi(0)
{
}

Map::~Map()
{
  for (int y = 0; y < height + 2; ++y)
    {
      for (int x = 0; x < width + 2; ++x)
  	{
  	  for (auto iterator = board[y][x].begin(); iterator != board[y][x].end(); ++iterator)
  	    delete (*iterator);
  	  board[y][x].clear();
  	}
    }
   delete [] board;
}

void	Map::updateMap(gdl::AShader &, const gdl::Clock &_clock, gdl::Input &_input, const glm::vec3 &)
{
  std::vector<AEntity *>::iterator tmp;

  for (auto entityIterator = listEntity.begin(); entityIterator != listEntity.end(); ++entityIterator)
    {
      for (int y = 0; y < height + 2 ; ++y)
	{
	  for (int x = 0; x < width + 2 ; ++x)
	    {
	      tmp = board[y][x].end();
	      for (auto iterator = board[y][x].begin(); iterator != board[y][x].end(); ++iterator)
		{
		  if (tmp == iterator)
		    break ;
		  if ((*iterator)->getType() == *entityIterator)
		    (*iterator)->update(_clock, _input, this);
		  if (marvinEnd == board[y][x].end())
		    break ;
		}
	    }
	}
    }
}

void	Map::displayMap(gdl::AShader &_shader, const gdl::Clock &_clock,
			gdl::Input &, const glm::vec3 &cam)
{
  int	newcamx = cam.x - 16;
  int	newcamy = cam.y - cam.z;
  int	camxmax = width + 2;
  int	camymax = height + 2;

  if (newcamx < 0)
    newcamx = 0;
  if (cam.y - cam.z< 0)
    newcamy = 0;
  if (camxmax > newcamx + 31)
    camxmax = newcamx + 31;
  if (camymax > newcamy + 20)
    camymax = newcamy + 20;
  for (auto entityIterator = listEntity.begin(); entityIterator != listEntity.end(); ++entityIterator)
    for (int y = newcamy; y < camymax ; ++y)
      for (int x = newcamx ; x < camxmax ; ++x)
  	for (auto iterator = board[y][x].begin(); iterator != board[y][x].end(); ++iterator)
  	  {
  	    if ((*iterator)->getType() == *entityIterator)
	      (*iterator)->drawEntity(_shader, _clock);
	    if (marvinEnd == board[y][x].end())
	      break;
  	  }
}

void	Map::addToGenerate(const MapTypes key, const genFct func)
{
  boardGenerate[key] = func;
}

void	Map::generateMap(const MapTypes type)
{
  if (type == PRESETA
      || type == PRESETB)
    {
      height = 25;
      width = 25;
    }
  board = new std::vector<AEntity *>* [height + 2];
  for (int i = 0; i < height + 2; ++i)
    board[i] = new std::vector<AEntity *> [width + 2];

  addToGenerate(PRESETA, &Map::generatePresetA);
  addToGenerate(PRESETB, &Map::generatePresetB);
  addToGenerate(RANDOM, &Map::generateRandom);
  addToGenerate(CUSTOM, &Map::generateCustom);
  addToGenerate(LOAD, &Map::generateLoad);

  listEntity.push_back(WALL);
  listEntity.push_back(VOID_BLOCK);
  listEntity.push_back(BLOCK);
  listEntity.push_back(PLAYER);
  listEntity.push_back(BOMB);
  listEntity.push_back(POWERUP);
  listEntity.push_back(SPEEDUP);
  listEntity.push_back(BOMBUP);
  listEntity.push_back(EXPLOSION);

  for (int y = 0; y < height + 2; ++y)
    for (int x = 0; x < width + 2; ++x)
      {
	if (y == 0 || y == (height + 1) || x == 0 || x == (width + 1))
	  addElement(x, y, new Box(x, y, skin, WALL));
      }
  auto iterator = boardGenerate.find(type);
  auto ptr = iterator->second;
  (this->*ptr)();
}

void	Map::genTotalPlayer(void)
{
  totalPlayer = nbAi + nbPlayer;
}

void	Map::setNbPlayer(const int _nbPlayer)
{
  nbPlayer = _nbPlayer;
}

void	Map::setNbAi(const int _nbAi)
{
  nbAi = _nbAi;
}

void	Map::setSound(Sound *_sound)
{
  sound = _sound;
}

int	Map::getNbAi(void) const
{
  return nbAi;
}

int	Map::getNbPlayer(void) const
{
  return nbPlayer;
}

int	Map::getTotalPlayer(void) const
{
  return totalPlayer;
}

int	Map::getWidth(void) const
{
  return width;
}

int	Map::getHeight(void) const
{
  return height;
}

void	Map::gottaPlaySound(const Entity type)
{
  if (type == BOMB)
    sound->getSound(SDBOMB)->play();
  else if (type == PLAYER)
    {
      sound->getSound(SDGAMEOVER)->play();
      --totalPlayer;
    }
}


bool            Map::CheckRange2(int const x, int const y) const
{
  if (x + 2 >= width || x - 2 <= 0 || y + 2 >= height || y - 2 <= 0)
    return (false);
  if ((checkCharMove(x + 2, y) == true &&  checkCharMove(x, y + 2) == true)
      || (checkCharMove(x - 2, y) == true && checkCharMove(x, y - 2) == true)
      ||  (checkCharMove(x - 2, y) == true && checkCharMove(x, y + 2) == true)
      ||  (checkCharMove(x + 2, y) == true && checkCharMove(x, y - 2) == true)
      ||  (checkCharMove(x - 2, y) == true && checkCharMove(x + 2, y) == true)
      ||  (checkCharMove(x, y - 2) == true && checkCharMove(x, y + 2) == true))
    {
      return true;
    }
  return false;
}

AEntity		*Map::spawnChar(const int team, const unsigned int power,
			const unsigned int speed, const unsigned int maxBomb)
{
  AEntity	*marvin;

  for (unsigned int cap = 0; cap <= 100; ++cap)
    {
      int x = rand() % width + 2;
      int y = rand() % height + 2;

      if (checkElement(x, y, PLAYER) == false
	  && checkCharMove(x, y) == true
	  && ((checkCharMove(x + 1, y) == true &&  checkCharMove(x, y + 1) == true)
	      || (checkCharMove(x - 1, y) == true && checkCharMove(x, y - 1) == true)
	      ||  (checkCharMove(x - 1, y) == true && checkCharMove(x, y + 1) == true)
	      ||  (checkCharMove(x + 1, y) == true && checkCharMove(x, y - 1) == true)
	      ||  (checkCharMove(x - 1, y) == true && checkCharMove(x + 1, y) == true)
	      ||  (checkCharMove(x, y - 1) == true && checkCharMove(x, y + 1) == true))
	  && CheckRange2(x, y) == true)
	{
	  marvin = new Character(x, y, team, power, speed, maxBomb);
	  static_cast<Character *>(marvin)->setSkin(skin);
	  addElement(x, y, marvin);
	  return marvin;
	}
    }
  return NULL;
}

void	Map::addElement(const int x, const int y, AEntity *entity)
{
  if (entity->getId() == -1)
    {
      idCount += 1;
      entity->setId(idCount);
      entity->initGraph();
    }
  board[y][x].push_back(entity);
}

bool	lowToHight(AEntity *a, AEntity *b)
{
  return (a->getType() < b->getType());
}

// The generation of bonuses is setted to 15% by destruction of a block

void	Map::deleteElement(const int x, const int y, const int id)
{
  bool	gottaSpawn = false;

  std::sort (board[y][x].begin(), board[y][x].end(), lowToHight);
  for (auto iterator = board[y][x].begin(); iterator != board[y][x].end(); ++iterator)
    {
      if ((*iterator)->getId() == id)
	{
	  if ((*iterator)->getType() == BLOCK
	      && (rand() % 100) <= 15)
	    gottaSpawn = true;
	  if ((*iterator)->getType() == BOMB
	      || (*iterator)->getType() == PLAYER)
	    gottaPlaySound((*iterator)->getType());
	  iterator = board[y][x].erase(iterator);
	  marvinEnd = iterator;
	  if (gottaSpawn == true)
	    {
	      addElement(x, y, new Bonus(x, y, skin, static_cast<Entity>(11 + (rand() % 3 + 1))));
	      gottaSpawn = false;
	    }
	  if (iterator == board[y][x].end())
	    {
	      delete (*iterator);
	      return ;
	    }
	}
    }
}

bool	Map::checkElement(const int x, const int y, const Entity type) const
{
  for (auto iterator = board[y][x].begin(); iterator != board[y][x].end(); ++iterator)
    {
      if ((*iterator)->getType() == type)
	return true;
    }
  return false;
}

bool	Map::checkCharMove(const int x, const int y) const
{
  for (auto iterator = board[y][x].begin(); iterator != board[y][x].end(); ++iterator)
    {
      if ((*iterator)->getType() == WALL
	  || (*iterator)->getType() == BLOCK
	  || (*iterator)->getType() == BOMB)
	return false;
    }
  return true;
}

bool	Map::CheckCharMoveOnBomb(const int x, const int y) const
{
  if (y >= height || y <= 0 || x >= width || x <= 0)
    return false;
  else
    return (checkCharMove(x, y));
}

bool	Map::checkBombMove(const int x, const int y, std::pair<int, int> pos) const
{
  for (auto iterator = board[y][x].begin(); iterator != board[y][x].end(); ++iterator)
    {
      if ((*iterator)->getType() == BOMB)
	{
	  if (CheckCharMoveOnBomb(x + pos.first, y + pos.second) == false)
	    {
	      return false;
	    }
	  return true;
	}
    }
  return false;
}


bool	hightToLow(AEntity *a, AEntity *b)
{
  return (a->getType() > b->getType());
}

bool		Map::moveObject(const int oldx, const int oldy, const int newx,
				const int newy, const int)
{
  AEntity	*tmp;
  int            nbPlayer = 0;

  std::sort (board[oldy][oldx].begin(), board[oldy][oldx].end(), hightToLow);
  for (auto iterator = board[oldy][oldx].begin(); iterator != board[oldy][oldx].end(); ++iterator)
    {
      if ((*iterator)->getType() == PLAYER)
	{
	  tmp = *iterator;
	  board[newy][newx].push_back(tmp);
	  ++nbPlayer;
	}
    }
  while (nbPlayer > 0)
    {
      marvinEnd = board[oldy][oldx].erase(board[oldy][oldx].end() - 1);
      --nbPlayer;
    }
  return true;
}

AEntity	*Map::getEntity(const int x, const int y, const int id) const
{
  for (auto iterator = board[y][x].begin(); iterator != board[y][x].end(); ++iterator)
    {
      if ((*iterator)->getId() == id)
	return *iterator;
    }
  return NULL;
}

std::vector<AEntity *>	*Map::getVecEntityAt(const int x, const int y) const
{
  return &board[y][x];
}

std::vector<AEntity *>	**Map::getBoard(void) const
{
  return board;
}

unsigned int	Map::getLastTeam(void)
{
  for (int y = 0; y < height + 2 ; ++y)
    for (int x = 0; x < width + 2 ; ++x)
      for (auto iterator = board[y][x].begin(); iterator != board[y][x].end(); ++iterator)
	{
	  if ((*iterator)->getType() == PLAYER)
	    return (static_cast<Character *>(*iterator)->getTeam());
	}
  return (-1);
}
