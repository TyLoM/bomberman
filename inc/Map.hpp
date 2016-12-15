//
// Map.hpp for qwwe in /home/lee_c/gitdepot/bomberman/src
//
// Made by soomin lee
// Login   <lee_c@epitech.net>
//
// Started on  Tue May 26 16:09:31 2015 soomin lee
// Last update Sun Jun 14 22:48:28 2015 david tang
//

#ifndef MAP_HPP_
# define MAP_HPP_

# include <vector>
# include <map>
# include "Character.hpp"
# include "Box.hpp"
# include "Texture.hpp"
# include "Sound.hpp"

class Character;

enum	MapTypes
  {
    RANDOM,
    PRESETA,
    PRESETB,
    LOAD,
    CUSTOM
  };



class	Map
{
  typedef void	(Map::*genFct)(void);
  // Mutex			*mutex;
  // CondVar			*cond;
private:
  std::vector<AEntity *>		**board;
  std::vector<Entity>			listEntity;
  std::map<MapTypes, genFct>		boardGenerate;
  std::vector<AEntity *>::iterator	marvinEnd;
  Texture				*skin;
  int					width;
  int					height;
  int					idCount;
  int					nbPlayer;
  int					nbAi;
  int					totalPlayer;
  Sound					*sound;

public:
  Map(const int _width, const int _height, Texture *_skin);
  ~Map();

public:
  void				displayMap(gdl::AShader &_shader, const gdl::Clock &_clock,
					   gdl::Input &, const glm::vec3 &);
  void			        genTotalPlayer(void);

public:
  void				addToGenerate(const MapTypes key, const genFct func);
  void				generateMap(const MapTypes type);
  void				generatePresetA(void);
  void				generatePresetB(void);
  void				generateLoad(void);
  void			        generateCustom(void);
  void			        generateRandom(void);
  void				generateBlocks(const int howMany, const Entity type);
  void				updateMap(gdl::AShader &_shader, const gdl::Clock &_clock,
					  gdl::Input &_input, const glm::vec3 &_cam);

public:
  void				setNbPlayer(const int nbPlayer);
  void				setNbAi(const int nbAi);
  void				setSound(Sound *_sound);
  void				setWidth(const int width);
  void				setHeight(const int height);

public:
  int				getWidth(void)			const;
  int				getHeight(void)			const;
  int				getNbAi(void)			const;
  int				getNbPlayer(void)		const;
  int				getTotalPlayer(void)		const;
  std::vector<AEntity *>	**getBoard(void)		const;
  void				gottaPlaySound(const Entity);
  AEntity			*spawnChar(const int team = DEFAULT_TEAM,
					   const unsigned int power = DEFAULT_POWER,
					   const unsigned int speed = DEFAULT_SPEED,
					   const unsigned int maxBomb = DEFAULT_MBOMB);

  AEntity			*getEntity(const int x, const int y, const int id) const;
  std::vector<AEntity *>	*getVecEntityAt(const int x, const int y) const;
  unsigned int			getLastTeam(void);

public:
  void				addElement(const int x, const int y, AEntity *element);
  bool				checkElement(const int x, const int y, const Entity type) const;
  bool				checkCharMove(const int x, const int y) const;
  bool				checkBombMove(const int x, const int y, std::pair<int, int>) const;
  bool				CheckCharMoveOnBomb(const int x, const int y) const;
  void				deleteElement(const int x, const int y, const int id);
  bool                          CheckRange2(int const x, int const y) const;

public:
  bool				moveObject(const int oldx, const int oldy,
					   const int newx, const int newy, const int id);
};

#endif
