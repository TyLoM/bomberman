//
// Menu.hpp for qwe in /home/quentin/bucket/bomberman
//
// Made by Quentin Richard
// Login   <quentin@epitech.net>
//
// Started on  Fri May 29 16:43:32 2015 Quentin Richard
// Last update Sun Jun 14 22:00:22 2015 Quentin Richard
//

#ifndef MENU_H_
#define MENU_H_

# include "Geometry.hh"
# include "Texture.hh"
# include "GraphEngine.hpp"
# include "AEntity.hpp"
# include "Music.hpp"
# include "Police.hpp"

# define MENU_TEXTURE "./assets/Menu/Menu.tga"
# define MENU_GAME "./assets/Menu/GameMenu.tga"
# define MENU_BEFORE_GAME "./assets/Menu/MenuGameSelect.tga"
# define CREATE_MENU "./assets/Menu/CreateMapSelect.tga"
# define OPTION_MENU "./assets/Menu/OptionMenu.tga"
# define SCORE_MENU "./assets/Menu/ScoreMenu.tga"
# define LOADING "./assets/Menu/Loading.tga"
# define CALL_PTR_FUNCTION(object, ptr_fct) ((object).*(ptr_fct))

class Menu
{
public:
  typedef bool  (Menu::*lvlMenu)();

public:
  Menu(GraphEngine *, Save *, AEntity *);
  ~Menu();

public:
  bool          initGraph();
  void	       	pushUv();
  bool		update();
  void		draw();
  bool		mainMenu();
  bool		selectMenu();
  bool		gameMenu();
  bool		createMapMenu();
  void		learnFunction(lvlMenu);
  glm::mat4	getTransformation() const;
  bool		checkExit(const int &, const int &);
  void		checkPlay(const int &, const int &);
  void		checkReturn(const int &, const int &);
  void		checkCreateMap(const int &, const int &);
  bool		checkLoadGame(const int &, const int &);
  void		checkNewGame(const int &, const int &);
  bool		startGame(const int &, const int &);
  bool		startCreateMap(const int &, const int &);
  void		returnMenu(const int &, const int &);
  void		checkScore(const int &, const int &);
  void		checkOption(const int &, const int &);
  void		checkGameReturn(const int &, const int &);
  bool		optionMenu();
  bool		scoreMenu();
  void		checkReturnScore(const int &, const int &);
  void		checkSave(const int &, const int &);
  void		checkReturnOption(const int &, const int &);
  void		checkLessPlayer(const int &, const int &);
  void		checkMorePlayer(const int &, const int &);
  void		checkMoreAI(const int &, const int &);
  void		checkLessAI(const int &, const int &);
  void		checkLessMap(const int &, const int &);
  void		checkMoreMap(const int &, const int &);
  void		checkLessSound(const int &, const int &);
  void		checkMoreSound(const int &, const int &);
  void		checkHeightMore(const int &, const int &);
  void		checkHeightLess(const int &, const int &);
  void		checkWidthMore(const int &, const int &);
  void		checkWidthLess(const int &, const int &);

private:
  std::vector<std::string>	nameMap;
  GraphEngine			*win;
  Save				*save;
  gdl::Geometry			geometry;
  gdl::Texture			tex;
  gdl::Texture			tex2;
  gdl::Texture			tex3;
  gdl::Texture			tex4;
  gdl::Texture			tex5;
  gdl::Texture			tex6;
  gdl::Texture			texLoad;
  int				lvl;
  int				check;
  int				nbPlayer;
  int				nbAI;
  int				setMap;
  int				soundM;
  int				soundGame;
  int				soundCreateMap;
  int				heightMap;
  int				widthMap;
  std::vector<lvlMenu>		selectLvl;
  glm::vec3			pos;
  glm::vec3			rot;
  glm::vec3			scale;
  Music				music;
  sf::Music			*sound;
  AEntity			*pol;
};

#endif
