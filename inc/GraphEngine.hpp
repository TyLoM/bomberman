//
// GraphEngine.hpp for Bomberman in /home/mcnama_d/gitreps/B4-CPP/bomberman/inc
//
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
//
// Started on  Thu Jun  4 21:13:35 2015 Duncan McNAMARA
// Last update Sat Jun 13 19:07:41 2015 Quentin Richard
//

#ifndef GRAPHENGINE_H_
# define GRAPHENGINE_H_

# include <iostream>
# include "Game.hh"
# include "Clock.hh"
# include "Input.hh"
# include "SdlContext.hh"
# include "Geometry.hh"
# include "Texture.hh"
# include "BasicShader.hh"
# include "Model.hh"
# include "Box.hpp"
# include "Map.hpp"
# include "Save.hh"
# include "Sound.hpp"

// # include <glm/glm.hpp>
// # include <glm/gtc/matrix_transform.hpp>

/*
** define the windows size here.
*/

# define WIN_HEIGHT 768
# define WIN_WIDTH 1024
# define CALL_PTR_FUNCTION(object, ptr_fct) ((object).*(ptr_fct))

/*
** The enum Event_key must be use for get the different event we need so add event when you found one.
*/

class			GraphEngine : public gdl::Game
{
public:
  GraphEngine();
  ~GraphEngine();

public:
  virtual bool		initialize();
  virtual bool		update();
  virtual void		draw();

public:
  gdl::SdlContext	getCtxt() const; // temporaire
  gdl::Input		*getInput(); // ne peut pas etre const
  gdl::Clock		getClock() const;
  gdl::BasicShader	*getShader();
  sf::Music		*getSound(Sounds type);
  Sound			*getPtrSound(void);

private:
  gdl::SdlContext	ctxt;
  gdl::Clock		clock;
  gdl::Input		input;
  gdl::BasicShader	shader;

private:
  Sound			*sound;
};

#endif /* !GRAPHENGINE_H_ */
