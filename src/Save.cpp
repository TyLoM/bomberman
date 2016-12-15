//
// Save.cpp for  in /home/tang_i/bucket/bomberman/src
//
// Made by david tang
// Login   <tang_i@epitech.net>
//
// Started on  Mon Jun  1 15:59:00 2015 david tang
// Last update Sun Jun 14 22:04:38 2015 Duncan McNAMARA
//

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "Save.hh"
#include "Texture.hpp"

Save::Save() :  mode(1), nbAi(0)
{
  err_folder = system("mkdir -p saves");
  generateMap();
}

Save::~Save()
{
}

void	Save::generateMap()
{
  ref["0"] = PLAYER;
  ref["1"] = VOID_BLOCK;
  ref["2"] = BLOCK;
  ref["3"] = WALL;
  ref["4"] = CURSOR1;
  ref["5"] = CURSOR2;
  ref["6"] = BACKGROUND;
  ref["7"] = GROUND;
  ref["8"] = YOUWIN;
  ref["9"] = YOULOSE;
  ref["10"] = EXPLOSION;
  ref["11"] = BOMB;
  ref["12"] = POWERUP;
  ref["13"] = SPEEDUP;
  ref["14"] = BOMBUP;
  ref["15"] = ENB;
}

bool		Save::addElement(int x, int y, Entity nameType)
{
  bool		success = false;

  TiXmlElement	*type = new TiXmlElement("NameType");
  getElem()->LinkEndChild(type);
  type->SetAttribute("Type", nameType);
  type->SetAttribute("Position_x", x);
  type->SetAttribute("Position_y", y);
  if (actual == MAP)
    success = doc.SaveFile("./saves/custom.xml");
  else
    success = doc.SaveFile("./saves/save.xml");
  return (success);
}

bool		Save::addCharacter(int x, int y, Entity nameType,
				   Character *characters)
{
  bool		success = false;

  TiXmlElement	*type = new TiXmlElement("Character");
  getElem()->LinkEndChild(type);
  type->SetAttribute("Player", nameType);
  type->SetAttribute("Position_x", x);
  type->SetAttribute("Position_y", y);
  type->SetAttribute("Team", characters->getTeam());
  type->SetAttribute("Power", characters->getPower());
  type->SetAttribute("Speed", characters->getSpeed());
  type->SetAttribute("Bomb", characters->getMaxbomb());
  if (actual == MAP)
    success = doc.SaveFile("./saves/custom.xml");
  else
    success = doc.SaveFile("./saves/save.xml");
  return (success);
}

bool				Save::createXml(Map *save)
{
  Map				*bis = save;
  std::vector<AEntity *>	**mapBis = bis->getBoard();
  TiXmlElement			*size = new TiXmlElement("Size");

  getElem()->LinkEndChild(size);
  size->SetAttribute("Width", bis->getWidth());
  size->SetAttribute("Height", bis->getHeight());
  size->SetAttribute("Mode", bis->getNbPlayer());
  size->SetAttribute("Ai", bis->getNbAi());
  setMode(bis->getNbPlayer());
  for (int y = 1; y < bis->getHeight() + 1; ++y)
    for (int x = 1; x < bis->getWidth() + 1; ++x)
      for (auto iterator = mapBis[y][x].begin(); iterator != mapBis[y][x].end(); ++iterator)
	if ((*iterator)->getType() != VOID_BLOCK && (*iterator)->getType() != EXPLOSION
	    && (*iterator)->getType() != BOMB)
	  {
	    if ((*iterator)->getType() == PLAYER)
	      {
	    	if (addCharacter(x, y, (*iterator)->getType(), static_cast<Character *>(*iterator)) == false)
	    	  return (false);
	      }
	    else if (addElement(x, y, (*iterator)->getType()) == false)
	      return (false);
	  }
  return (true);
}

void	Save::selectType(SaveType type)
{
  if (type == MAP)
    actual = type;
  else
    actual = SAVE;
}

bool	Save::saveFile(Map *save, SaveType type)
{
  if (getFolder() == -1)
    {
      std::cerr << "Can't Save file!!" << std::endl;
      return (false);
    }
  else
    {
      TiXmlDocument newdoc;
      doc = newdoc;
      TiXmlElement *newroot = new TiXmlElement("Save");
      root = newroot;
      doc.LinkEndChild(root);
      selectType(type);
      if (createXml(save) == false)
	std::cout << "Can't saved!" << std::endl;
      else
	std::cout << "Game Saved!" << std::endl;
    }
  doc.Clear();
  return (true);
}

bool		Save::retrieveData(TiXmlElement	*elem)
{
  std::string	elemName;

  for (elem = rootLoad->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
    {
      elemName = elem->Value();
      if (elemName == "NameType")
	{
	  if (!buildMap(elem))
	    return false;
	}
      else if (elemName == "Character")
	{
	  if (!buildCharacter(elem))
	    return false;
	}
    }
  return true;
}

bool		Save::buildMap(TiXmlElement *elem)
{
  std::string	type;
  const char	*attr;
  int		x = 0;
  int		y = 0;

  if ((attr = elem->Attribute("Type")) != NULL)
    type = attr;
  else
    return false;
  if ((attr = elem->Attribute("Position_x")) != NULL)
    {
      std::istringstream buffer(attr);
      buffer >> x;
    }
  else
    return false;
  if ((attr = elem->Attribute("Position_y")) != NULL)
    {
      std::istringstream buffer(attr);
      buffer >> y;
    }
  else
    return false;
  map->addElement(x, y, new Box(x, y, skin, ref[type]));
  return true;
}

bool	Save::retrieveDetail(TiXmlElement *elem, int &x, int &y, int &team)
{
  const char	*attr;

  if ((attr = elem->Attribute("Position_x")) != NULL)
    {
      std::istringstream buffer(attr);
      buffer >> x;
    }
  else
    return false;
  if ((attr = elem->Attribute("Position_y")) != NULL)
    {
      std::istringstream buffer(attr);
      buffer >> y;
    }
  else
    return false;
  if ((attr = elem->Attribute("Team")) != NULL)
    {
      std::istringstream buffer(attr);
      buffer >> team;
    }
  else
    return false;
  return true;
}

bool	Save::retrieveSpec(TiXmlElement *elem, int &power, unsigned int &speed, unsigned int &maxBomb)
{
  const char	*attr;

  if ((attr = elem->Attribute("Power")) != NULL)
    {
      std::istringstream buffer(attr);
      buffer >> power;
    }
  else
    return false;
  if ((attr = elem->Attribute("Speed")) != NULL)
    {
      std::istringstream buffer(attr);
      buffer >> speed;
    }
  else
    return false;
  if ((attr = elem->Attribute("Bomb")) != NULL)
    {
      std::istringstream buffer(attr);
      buffer >> maxBomb;
    }
  else
    return false;
  return true;
}

bool		Save::buildCharacter(TiXmlElement *elem)
{
  int		x = 0;
  int		y = 0;
  int		team = 0;
  int		power = 0;
  AEntity	*marvin;
  unsigned int	speed = 0;
  unsigned int	maxBomb = 0;

  if (!retrieveDetail(elem, x, y, team))
    return false;
  if (!retrieveSpec(elem, power, speed, maxBomb))
    return false;
  marvin = new Character(x, y, team, power, speed, maxBomb);
  static_cast<Character *>(marvin)->setSkin(skin);
  map->addElement(x, y, marvin);
  return true;
}

bool	Save::retrieveMap(TiXmlElement *elem, int &w, int &h)
{
  const char	*attr;

  if ((attr = elem->Attribute("Width")) != NULL)
    {
      std::istringstream buffer(attr);
      buffer >> w;
    }
  else
    return false;
  if ((attr = elem->Attribute("Height")) != NULL)
    {
      std::istringstream buffer(attr);
      buffer >> h;
    }
  else
    return false;
  return true;
}

bool	Save::retrieveMode(TiXmlElement *elem, int &w, int &h, int &o, int &a)
{
  const char	*attr;

  if (!retrieveMap(elem, w, h))
    return false;
  if ((attr = elem->Attribute("Mode")) != NULL)
    {
      std::istringstream buffer(attr);
      buffer >> o;
    }
  else
    return false;
  if ((attr = elem->Attribute("Ai")) != NULL)
    {
      std::istringstream buffer(attr);
      buffer >> a;
    }
  else
    return false;
  return (true);
}

bool		Save::retrieveInfo()
{
  TiXmlElement	*elem;
  std::string	elemName;
  int		w = 0;
  int		h = 0;
  int		o = 0;
  int		a = 0;

  elem = rootLoad->FirstChildElement();
  elemName = elem->Value();
  if (elemName == "Size")
    {
      if (!retrieveMode(elem, w, h, o, a))
	return false;
    }
  else
    return false;
  skin = new Texture;
  skin->initialize();
  map = new Map(w, h, skin);
  map->generateMap(LOAD);
  retrieveData(elem);
  setMode(o);
  return (true);
}

bool	Save::loadXml()
{
  TiXmlDocument file;
  docLoad = file;
  std::cout << "actual "<< actual<< std::endl;
  if (actual == MAP)
     {
      if (!docLoad.LoadFile("./saves/custom.xml"))
	return (false);
    }
  else
    {
      if (!docLoad.LoadFile("./saves/save.xml"))
  	return (false);
    }
  if((rootLoad = docLoad.FirstChildElement()) == NULL)
    {
      docLoad.Clear();
      return (false);
    }
  if (!retrieveInfo())
    return false;
  return (true);
}

Map	*Save::loadFile(SaveType type)
{
  if (getFolder() == -1)
    {
      std::cerr << "Can't Load file!!" << std::endl;
      return (NULL);
    }
  else
    {
      actual = type;
      if (loadXml() == false)
	std::cout << "Can't load!" << std::endl;
      else
	std::cout << "Game Loaded!" << std::endl;
    }
  doc.Clear();
  return (map);
}

int	Save::getFolder() const
{
  return (err_folder);
}

TiXmlDocument	Save::getDoc() const
{
  return (doc);
}

TiXmlElement	*Save::getElem() const
{
  return (root);
}

Map	*Save::getSave() const
{
  return (map);
}

void	Save::setState(const bool change)
{
  state = change;
}

bool	Save::getState()
{
  return (state);
}

bool		Save::checkFile(const char *filename) const
{
  std::ifstream	ifile(filename);
  return (ifile.good());
}

bool		Save::fileExist(const SaveType type) const
{
  bool		ret = false;

  if (type == MAP)
    ret = checkFile("./saves/custom.xml");
  else
    ret = checkFile("./saves/save.xml");
 return (ret);
}

void	Save::setMode(const int _nbplayer)
{
  mode = _nbplayer;
}

void	Save::setNbAi(const int _nbAi)
{
  nbAi = _nbAi;
}

int	Save::getMode() const
{
  return (mode);
}

int	Save::getNbAi() const
{
  return (nbAi);
}

void	Save::setSaveFile(const SaveType type)
{
  actual = type;
}

SaveType	Save::getSaveFile() const
{
  return actual;
}
