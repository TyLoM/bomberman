//
// Character.cpp for lol in /home/tylo/rendu/bomberman
//
// Made by TyLo
// Login   <tylo@epitech.net>
//
// Started on  Sun Jun 14 06:04:56 2015 TyLo
// Last update Sun Jun 14 23:03:38 2015 Duncan McNAMARA
//

#include "Character.hpp"
#include "Error.hpp"
#include "Bomb.hpp"
#include <cmath>

Character::Character(const int _x, const int _y,
		     const int _team,
		     const int _power,
		     const unsigned int _speed,
		     const unsigned int _maxBomb,
		     const Entity _type)
  : AEntity(_x, _y, _type), x(_x), y(_y), skin(NULL), power(_power), speed(_speed), maxBomb(_maxBomb),
    curBomb(_maxBomb), vdir(glm::vec3(0, -0.05, 0)), moving(false), running(false), team(_team), score(0), cursor(NULL)
{
}

Character::~Character()
{
  if (cursor != NULL)
    delete cursor;
}

bool		Character::initGraph(void)
{
  if (team == 1)
    {
      olddir = SDLK_DOWN;
      cursor = new Box(x, y, skin, CURSOR1);
      cursor->initGraph();
    }
  else if (team == 2)
    {
      olddir = SDLK_s;
      cursor = new Box(x, y, skin, CURSOR2);
      cursor->initGraph();
    }
  else
    olddir = DOWN;
  pos += glm::vec3(0, 0, -0.5);
  scale *= glm::vec3(0.0024, 0.0024, 0.0024);
  rot += glm::vec3(90, 0, 0);
  if (!model.load("../LibBomberman_linux_x64/assets/marvin.fbx"))
    throw Error("Failed to load the marvin model");
  model.createSubAnim(0, "start", 0, 31);
  model.createSubAnim(0, "running", 31, 54);
  model.createSubAnim(0, "stop", 54, 121);
  timer = 0.0;
  init();
  return true;
}

void		Character::init(void)
{
  if (team == 1)
    {
      mvFcts[SDLK_LEFT][SDLK_UP] = &Character::rotA;
      mvFcts[SDLK_LEFT][SDLK_DOWN] = &Character::rotB;
      mvFcts[SDLK_LEFT][SDLK_RIGHT] = &Character::rotC;
      mvFcts[SDLK_LEFT][SDLK_LEFT] = &Character::nothing;

      mvFcts[SDLK_RIGHT][SDLK_DOWN] = &Character::rotA;
      mvFcts[SDLK_RIGHT][SDLK_UP] = &Character::rotB;
      mvFcts[SDLK_RIGHT][SDLK_LEFT] = &Character::rotC;
      mvFcts[SDLK_RIGHT][SDLK_RIGHT] = &Character::nothing;

      mvFcts[SDLK_UP][SDLK_RIGHT] = &Character::rotA;
      mvFcts[SDLK_UP][SDLK_LEFT] = &Character::rotB;
      mvFcts[SDLK_UP][SDLK_DOWN] = &Character::rotC;
      mvFcts[SDLK_UP][SDLK_UP] = &Character::nothing;

      mvFcts[SDLK_DOWN][SDLK_LEFT] = &Character::rotA;
      mvFcts[SDLK_DOWN][SDLK_RIGHT] = &Character::rotB;
      mvFcts[SDLK_DOWN][SDLK_UP] = &Character::rotC;
      mvFcts[SDLK_DOWN][SDLK_DOWN] = &Character::nothing;

      dirMap[UP] = SDLK_UP;
      dirMap[DOWN] = SDLK_DOWN;
      dirMap[LEFT] = SDLK_LEFT;
      dirMap[RIGHT] = SDLK_RIGHT;
    }
  else if (team == 2)
    {
      mvFcts[SDLK_q][SDLK_z] = &Character::rotA;
      mvFcts[SDLK_q][SDLK_s] = &Character::rotB;
      mvFcts[SDLK_q][SDLK_d] = &Character::rotC;
      mvFcts[SDLK_q][SDLK_q] = &Character::nothing;

      mvFcts[SDLK_d][SDLK_s] = &Character::rotA;
      mvFcts[SDLK_d][SDLK_z] = &Character::rotB;
      mvFcts[SDLK_d][SDLK_q] = &Character::rotC;
      mvFcts[SDLK_d][SDLK_d] = &Character::nothing;

      mvFcts[SDLK_z][SDLK_d] = &Character::rotA;
      mvFcts[SDLK_z][SDLK_q] = &Character::rotB;
      mvFcts[SDLK_z][SDLK_s] = &Character::rotC;
      mvFcts[SDLK_z][SDLK_z] = &Character::nothing;

      mvFcts[SDLK_s][SDLK_q] = &Character::rotA;
      mvFcts[SDLK_s][SDLK_d] = &Character::rotB;
      mvFcts[SDLK_s][SDLK_z] = &Character::rotC;
      mvFcts[SDLK_s][SDLK_s] = &Character::nothing;

      dirMap[UP] = SDLK_z;
      dirMap[DOWN] = SDLK_s;
      dirMap[LEFT] = SDLK_q;
      dirMap[RIGHT] = SDLK_d;
    }
}

void		Character::rotA(void)
{
  frotate(glm::vec3(0, 1, 0), 90);
  rotateDir(90);
}

void		Character::rotB(void)
{
  frotate(glm::vec3(0, 1, 0), -90);
  rotateDir(-90);
}

void		Character::rotC(void)
{
  frotate(glm::vec3(0, 1, 0), 180);
  rotateDir(180);
}

void		Character::nothing(void)
{
  return;
}

int		Character::getRoudedX() const
{
  return (round(pos.x));
}

int		Character::getRoudedY() const
{
  return (round(pos.y));
}

int		Character::getBombX(Map const *board) const
{
  int	realPos;

  if (board->getWidth() == getX())
    realPos = board->getWidth();
  else if (getX() == 0)
    realPos = 1;
  else
    realPos = getRoudedX();
  return (realPos);
}

int		Character::getBombY(Map const *board) const
{
  int	realPos;

  if (board->getHeight() == getY())
    realPos = board->getHeight();
  else if (getY() == 0)
    realPos = 1;
  else
    realPos = getRoudedY();
  return (realPos);
}

void		Character::update(const gdl::Clock &clock, gdl::Input &input, Map *board)
{
  int		key;

  timer -= clock.getElapsed();
  key = 0;

  if (((input.getKey(SDLK_SPACE) && team == 2) ||
       (input.getKey(SDLK_RETURN) && team == 1)) &&
      curBomb > 0 &&
      board->checkElement(getBombX(board), getBombY(board), BOMB) == false)
    {
      board->addElement(getBombX(board), getBombY(board), new Bomb(getBombX(board), getBombY(board), this, getPower()));
      --curBomb;
    }
  if (((input.getKey(SDLK_LEFT) || input.getKey(SDLK_RIGHT) ||
	input.getKey(SDLK_UP) || input.getKey(SDLK_DOWN)) && team == 1) ||
      ((input.getKey(SDLK_q) || input.getKey(SDLK_d) ||
	input.getKey(SDLK_s) || input.getKey(SDLK_z)) && team == 2))
    {
      while (input.getKey(dirMap[key]) == false)
	++key;
      if (moving == false)
      	{
      	  moving = true;
      	  model.setCurrentSubAnim("start", moving);
      	  timer = 120 * model.getFrameDuration();
      	}
      else if (moving == true && timer < 89 * model.getFrameDuration() &&
	      timer > 64 * model.getFrameDuration() && running == false)
	{
	  model.setCurrentSubAnim("running", moving);
	  running = true;
	}
      auto iterator = mvFcts[dirMap[key]].find(olddir);
      auto ptr = iterator->second;
      (this->*ptr)();
      olddir = dirMap[key];
      move(board);
    }
  else if (moving == true)
    {
      if (running == true)
	{
	  running = false;
	  model.setCurrentSubAnim("stop", moving);
	  timer = 66 * model.getFrameDuration();
	}
      else
	{
	  moving = false;
	  model.setCurrentSubAnim("stop", false);
	}
    }
  if (cursor != NULL)
    cursor->update(clock, input, board);
}

void		Character::moveRight(Map *board, glm::vec3 &_pos)
{
  bool		checker;
  double	y;
  double	z;
  float		speed_res;

  y = modf(_pos.y, &z);
  checker = board->checkCharMove(static_cast<int>(_pos.x + 0.8), static_cast<int>(_pos.y + 0.7));
  if (checker == true  && y <= 0.7 && y >= 0.33)
    checker = board->checkCharMove(static_cast<int>(_pos.x + 0.8), static_cast<int>(_pos.y - y));
  if (checker == false)
    {
      std::pair<int, int> pos(1, 0);
      checker = board->checkBombMove(round(_pos.x), round(_pos.y), pos);
    }
  if (checker == true)
    {
      speed_res = 1.0 + 0.5 * speed;
      pickUp(static_cast<int>(_pos.x + 0.7), static_cast<int>(_pos.y + 0.7), board);
      _pos += (vdir * glm::vec3(speed_res, speed_res, speed_res));
      if (cursor != NULL)
	cursor->ftranslate(vdir * glm::vec3(speed_res, speed_res, speed_res));
    }
}

void		Character::moveLeft(Map *board, glm::vec3 &_pos)
{
  bool		checker;
  double	y;
  double	z;
  float		speed_res;

  y = modf(_pos.y, &z);
  checker = board->checkCharMove(static_cast<int>(_pos.x + 0.1), static_cast<int>(_pos.y + 0.7));
  if (y <= 0.7 && y >= 0.33)
    if (checker == true)
      checker = board->checkCharMove(static_cast<int>(_pos.x + 0.1), static_cast<int>(_pos.y + 0.3));
  if (checker == false && y != -1)
    {
      std::pair<int, int> pos(-1, 0);
      checker = board->checkBombMove(round(_pos.x), round(_pos.y), pos);
    }
  if (checker == true)
    {
      speed_res = 1.0 + 0.5 * speed;
      pickUp(static_cast<int>(_pos.x + 0.3), static_cast<int>(_pos.y + 0.7), board);
      _pos += (vdir * glm::vec3(speed_res, speed_res, speed_res));
      if (cursor != NULL)
	cursor->ftranslate(vdir * glm::vec3(speed_res, speed_res, speed_res));
    }
}

void		Character::moveDown(Map *board, glm::vec3 &_pos)
{
  bool		checker;
  double	x;
  double	z;
  float		speed_res;

  x = modf(_pos.x, &z);
  checker = board->checkCharMove(static_cast<int>(_pos.x + 0.7), static_cast<int>(_pos.y + 0.1));
  if (checker == true && x <= 0.7 && x >= 0.33)
    checker = board->checkCharMove(static_cast<int>(_pos.x + 0.3), static_cast<int>(_pos.y + 0.3));
  if (checker == false)
    {
      std::pair<int, int> pos(0, -1);
      checker = board->checkBombMove(static_cast<int>(_pos.x + 0.7), static_cast<int>(_pos.y + 0.6), pos);
    }
  if (checker == true)
    {
      speed_res = 1.0 + 0.5 * speed;
      pickUp(static_cast<int>(_pos.x + 0.3), static_cast<int>(_pos.y + 0.3), board);
      _pos += (vdir * glm::vec3(speed_res, speed_res, speed_res));
      if (cursor != NULL)
	cursor->ftranslate(vdir * glm::vec3(speed_res, speed_res, speed_res));
    }
}

void		Character::moveUpOrRight(Map *board, glm::vec3 &_pos)
{

  if ((olddir == SDLK_UP && team == 1) || (olddir == SDLK_z && team == 2))
    moveUp(board, _pos);
  else
    moveRight(board, _pos);

}

void		Character::moveUp(Map *board, glm::vec3  &_pos)
{
  bool		checker;
  double	x;
  double	z;
  float		speed_res;

  x = modf(_pos.x, &z);
  checker = board->checkCharMove(static_cast<int>(_pos.x + 0.7), static_cast<int>(_pos.y + 0.9));
  if (checker == true && x <= 0.7 && x >= 0.33)
    checker = board->checkCharMove(static_cast<int>(_pos.x - 0.1), static_cast<int>(_pos.y + 0.7));
  if (checker == false)
    {
      std::pair<int, int> pos(0, 1);
      checker = board->checkBombMove(static_cast<int>(_pos.x + 0.7), static_cast<int>(_pos.y + 0.9), pos);
    }
  if (checker == true)
    {
      speed_res = 1.0 + 0.5 * speed;
      pickUp(static_cast<int>(_pos.x + 0.7), static_cast<int>(_pos.y + 0.7), board);
      _pos += (vdir * glm::vec3(speed_res, speed_res, speed_res));
      if (cursor != NULL)
	cursor->ftranslate(vdir * glm::vec3(speed_res, speed_res, speed_res));
    }
}

void		Character::move(Map *board)
{
  float		speed_res;
  glm::vec3	_pos = pos;

  speed_res = 1.0 + 0.5 * speed;
  _pos += (vdir * glm::vec3(speed_res, speed_res, speed_res));
  if ((olddir == SDLK_UP && team == 1) || (olddir == SDLK_z && team == 2)
      || (olddir == SDLK_RIGHT && team == 1) || (olddir == SDLK_d && team == 2))
    moveUpOrRight(board, pos);
  else if ((olddir == SDLK_DOWN && team == 1) || (olddir == SDLK_s && team == 2))
      moveDown(board, pos);
  else
    moveLeft(board, pos);
  if (round(pos.x) != x)
    {
      board->moveObject(x, y, round(pos.x), round(pos.y), id);
      x = round(pos.x);
    }
  if (round(pos.y) != y)
    {
      board->moveObject(x, y, round(pos.x), round(pos.y), id);
      y = round(pos.y);
    }
}

void		Character::drawEntity(gdl::AShader &_shader, const gdl::Clock &_clock)
{
  model.draw(_shader, getTransformation(), _clock.getElapsed());
  if (cursor != NULL)
    cursor->drawEntity(_shader, _clock);
}

void		Character::pickUp(int x, int y, Map *board)
{
  int		id = -1;
  std::vector<AEntity *> *bonus;
  std::vector<AEntity *>::iterator it;

  bonus = board->getVecEntityAt(x, y);
  for (it = bonus->begin(); it != bonus->end() ; ++it)
    if ((*it)->getType() == POWERUP || (*it)->getType() == SPEEDUP || (*it)->getType() == BOMBUP)
      id = (*it)->getId();
  if (id != -1)
    {
      if (board->checkElement(x, y, POWERUP))
        alterPower(1);
      else if (board->checkElement(x, y, SPEEDUP))
	alterSpeed(1);
      else
	alterMaxBomb(1);
      board->deleteElement(x, y, id);
    }
}

void		Character::alterPower(const int _alteration)
{
  power = power +_alteration;
  if (power < DEFAULT_POWER)
    power = DEFAULT_POWER;
  else if (power > MAX_POWER)
    power = MAX_POWER;
}

void		Character::alterSpeed(const int _alteration)
{
  speed = speed + _alteration;
  if (speed < DEFAULT_SPEED)
    speed = DEFAULT_SPEED;
  else if (speed > MAX_SPEED)
    speed = MAX_SPEED;
}

void		Character::alterMaxBomb(const int _alteration)
{
  maxBomb = maxBomb + _alteration;
  if (maxBomb > MAX_MBOMB)
    maxBomb = MAX_MBOMB;
  else
    ++curBomb;
}

void		Character::rotateDir(float _angle)
{
  float		x;
  float		y;

  _angle = _angle * M_PI / 180;
  x = (vdir.x * cos(_angle) - vdir.y * sin(_angle));
  y = (vdir.x * sin(_angle) + vdir.y * cos(_angle));
  vdir.x = x;
  vdir.y = y;
}

int		Character::getTeam() const
{
  return (team);
}

unsigned int	Character::getSpeed() const
{
  return (speed);
}

int		Character::getPower() const
{
  return (power);
}

unsigned int	Character::getMaxbomb() const
{
  return (maxBomb);
}

unsigned int	Character::getCurBomb() const
{
  return (curBomb);
}

void		Character::setSkin(Texture *_skin)
{
  skin = _skin;
}

void		Character::setCurBomb(const unsigned int value)
{
  if (value > maxBomb)
    curBomb = maxBomb;
  else
    curBomb = value;
}

void		Character::incCurBomb()
{
  if (curBomb < maxBomb)
    ++curBomb;
}
