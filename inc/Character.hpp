//
// Character.hpp for qwe in /home/lee_c/gitdepot/bomberman/src
//
// Made by soomin lee
// Login   <lee_c@epitech.net>
//
// Started on  Sun May 24 16:09:15 2015 soomin lee
// Last update Sun Jun 14 07:56:23 2015 Antoine Qu
//

#ifndef CHARACTER_HPP_
# define CHARACTER_HPP_

#include "AEntity.hpp"
#include "Map.hpp"
#include "Model.hh"
#include "Texture.hpp"
#include "Box.hpp"

# define MAX_POWER	8
# define MAX_SPEED	5
# define MAX_MBOMB	5

class		Character : public AEntity
{
  enum		direction
    {
      UP,
      DOWN,
      LEFT,
      RIGHT
    };
  typedef void	(Character::*mvFct)(void);
private:
  /*
  ** Will need to add a pointer to a class item for the "special powers"
  ** that a character can have
  ** e.g: kick, detonation, ...
  */
  unsigned int	x;
  unsigned int	y;
  Texture	*skin;
  int		power;
  unsigned int	speed;
  unsigned int	maxBomb;
  unsigned int	curBomb;
  gdl::Model	model;
  glm::vec3	vdir;
  bool		moving;
  bool		running;
  int		olddir;
  float		timer;
  int		team;
  unsigned int	score;

  std::map<int, int>		dirMap;
  std::map<int, std::map<int, mvFct> >	mvFcts;

  Box		*cursor;

public:
  Character(const int _x, const int _y,
	    const int _team = DEFAULT_TEAM,
  	    const int _power = DEFAULT_POWER,
  	    const unsigned int _speed = DEFAULT_SPEED,
  	    const unsigned int _maxBomb = DEFAULT_MBOMB,
	    const Entity _type = PLAYER);
  ~Character();

public:
  void		init(void);
  virtual bool	initGraph(void);
  virtual void	update(const gdl::Clock &_clock, gdl::Input &_input,
		       Map *board);
  virtual void	drawEntity(gdl::AShader &_Shader, const gdl::Clock &_clock);

public:
  void		move(Map *board);
  void		rotA(void);
  void		rotB(void);
  void		rotC(void);
  void		nothing(void);
  void		alterPower(const int _alteration);
  void		alterSpeed(const int _alteration);
  void		alterMaxBomb(const int _alteration);
  void		rotateDir(const float _angle);
  void	        pickUp(int x, int y, Map *board);
  /*
  **  here will be the function to drop bombs but for that we need
  **    a map member function to add entities
  */
public:
  bool		dropBomb(Map *board);
  int		getTeam() const;
  int		getPower() const;
  unsigned int	getSpeed() const;
  unsigned int	getMaxbomb() const;
  int		getRoudedX() const;
  int		getRoudedY() const;
  unsigned int	getCurBomb() const;
  void		moveRight(Map *, glm::vec3&);
  void		moveUp(Map *, glm::vec3 &);
  void		moveUpOrRight(Map *, glm::vec3 &);
  void		moveLeft(Map *, glm::vec3 &);
  void		moveDown(Map *, glm::vec3 &);
  int	        getBombY(Map const *board) const;
  int		getBombX(Map const *board) const;

public:
  bool		moveAi(const gdl::Clock &, Map *);
  bool		searchItem(Map *, std::pair<int, int> &);
  bool		moveOver();
  bool		getItem();
  bool		checkAround(Map *, std::pair<int, int> &, unsigned int);
  bool		checkBomb(Map *, std::pair<int, int> &, unsigned int);
  bool		moveAway(Map *, std::pair<int, int> &);

public:
  void		setSkin(Texture *);
  void		setCurBomb(const unsigned int);

public:
  void		incCurBomb();
};

#endif
