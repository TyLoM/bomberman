//
// EditEngine.hpp for Bomberman in /home/mcnama_d/gitreps/B4-CPP/bomberman/src
// 
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
// 
// Started on  Tue Jun  9 15:37:32 2015 Duncan McNAMARA
// Last update Sun Jun 14 17:59:06 2015 Duncan McNAMARA
//

#ifndef EDITENGINE_HPP_
# define EDITENGINE_HPP_

# include "GraphEngine.hpp"
# include "Map.hpp"
# include "AEntity.hpp"
# include "EditBox.hpp"
# include "Music.hpp"

class		EditEngine
{
private:
  GraphEngine	*toGraph;
  Map		*board;
  EditBox	*box;
  Texture	*skin;
  Save		*save;
  Music		*music;
  AEntity	*back;
  unsigned int	volume;

public:
  EditEngine(GraphEngine *_toGraph, Save *_save, unsigned int _volume);
  ~EditEngine();

public:
  bool		initialize(const unsigned int _width, const unsigned int _height);
  bool		update();
  void		draw();

public:
  void		checkSave();

public:
  Map		*getMap() const;
  Save		*getSave() const;
};

#endif /* !EDITENGINE_HPP_ */
