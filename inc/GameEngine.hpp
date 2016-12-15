//
// GameEngine.hpp for Bomberman in /home/mcnama_d/gitreps/B4-CPP/bomberman/inc
//
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
//
// Started on  Thu Jun  4 21:22:46 2015 Duncan McNAMARA
// Last update Sun Jun 14 21:52:38 2015 Duncan McNAMARA
//

#ifndef GAMEENGINE_HPP_
# define GAMEENGINE_HPP_

# include "AEntity.hpp"
# include "GraphEngine.hpp"
# include "Music.hpp"
# include "Save.hh"

class		GameEngine
{
private:
  GraphEngine	*toGraph;
  Map		*testmap;
  AEntity	*marvin;
  AEntity	*marvin2;
  Texture	*skin;
  Save		*save;
  Music		*music;
  AEntity	*ground;
  AEntity	*back;
  unsigned int	nbPlayers;
  unsigned int	nbAi;
  unsigned int	volume;
  SaveType	saveType;
  bool		pause;

public:
  GameEngine(GraphEngine *_toGraph, Save *_save,
	     const unsigned int _nbPlayers,
	     const unsigned int _nbAi,
	     const unsigned int _volume,
	     const SaveType _saveType = DEFAULT);
  ~GameEngine();

public:
  bool		initialize(void);
  bool		update(void);
  void		draw(void);

public:
  void		onePlayerDraw(void);
  void		twoPlayerDraw(void);

public:
  void		checkSave();
  AEntity	*findCharacter(const int);

public:
  void		setNbAi(const int  nbAi);
  void		setNbPlayers(const int nbPlayers);

public:
  Map		*getMap(void) const;
  Save		*getSave(void) const;

public:
  bool		endGame(void);
  void		endDraw(Entity _type);
};

#endif /* !GAMEENGINE_HPP_ */
