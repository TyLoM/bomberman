//
// Save.hh for  in /home/tang_i/bucket/bomberman/src
//
// Made by david tang
// Login   <tang_i@epitech.net>
//
// Started on  Mon Jun  1 16:00:13 2015 david tang
// Last update Sun Jun 14 21:01:22 2015 david tang
//

#ifndef SAVE_HH_
# define SAVE_HH_

#include <map>
#include "Map.hpp"
#include "tinyxml.h"

enum		SaveType
  {
    DEFAULT,
    SETA,
    SETB,
    MAP,
    SAVE
  };

class					Save
{
private:
  int					err_folder;
  bool					state;
  TiXmlDocument				doc;
  TiXmlDocument				docLoad;
  TiXmlElement				*root;
  TiXmlElement				*rootLoad;
  Texture				*skin;
  Map					*map;
  int					mode;
  int					nbAi;
  std::map<std::string, Entity>       	ref;
  SaveType				actual;

public:
  Save();
  ~Save();
  void				generateMap();
  bool				saveFile(Map *, SaveType);

  //save game
  void				selectType(SaveType);
  bool				createXml(Map *);
  bool				addElement(int, int, Entity);
  bool				addCharacter(int, int, Entity, Character*);
  bool				presetMap();

  //load game
  Map				*loadFile(SaveType);
  bool				loadXml();
  bool				chooseFile();
  bool				retrieveInfo();
  bool				retrieveData(TiXmlElement *);
  bool				buildCharacter(TiXmlElement *);
  bool				retrieveDetail(TiXmlElement *, int &, int &, int &);
  bool				retrieveSpec(TiXmlElement *, int &, unsigned int &, unsigned int &);
  bool				retrieveMode(TiXmlElement *, int &, int &, int &, int &);
  bool				retrieveMap(TiXmlElement *, int &, int &);
  bool				buildMap(TiXmlElement *);
  bool				editMap(const int, const int);

  //getter & setter
public:
  TiXmlDocument			getDoc() const;
  TiXmlElement			*getElem() const;
  Map				*getSave() const;
  bool				getState();
  void				setState(const bool);
  void				setMode(const int);
  void				setNbAi(const int);
  void				setSaveFile(const SaveType);
  SaveType			getSaveFile() const;
  int				getMode() const;
  int				getNbAi() const;
  int				getFolder() const;
  bool				fileExist(const SaveType) const;
  bool				checkFile(const char *) const;
};

#endif
