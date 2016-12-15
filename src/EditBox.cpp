//
// EditBox.cpp for Bomberman in /home/mcnama_d/gitreps/B4-CPP/bomberman/src
// 
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
// 
// Started on  Tue Jun  9 16:14:01 2015 Duncan McNAMARA
// Last update Sun Jun 14 22:39:16 2015 david tang
//

#include "EditBox.hpp"
#include "Error.hpp"

EditBox::EditBox(Texture *_skin)
  : skin(_skin)
{
}

EditBox::~EditBox()
{
}
bool		EditBox::initialize(void)
{
  blocks.push_back(new Box(1, 1, skin, VOID_BLOCK));
  blocks.back()->initGraph();
  blocks.back()->ftranslate(glm::vec3(0, 0, 1.1));

  blocks.push_back(new Box(1, 1, skin, BLOCK));
  blocks.back()->initGraph();
  blocks.back()->ftranslate(glm::vec3(0, 0, 1.1));

  blocks.push_back(new Box(1, 1, skin, WALL));
  blocks.back()->initGraph();
  blocks.back()->ftranslate(glm::vec3(0, 0, 1.1));

  mvFcts[SDLK_LEFT] = &EditBox::moveLeft;
  mvFcts[SDLK_RIGHT] = &EditBox::moveRight;
  mvFcts[SDLK_UP] = &EditBox::moveUp;
  mvFcts[SDLK_DOWN] = &EditBox::moveDown;

  box = blocks[0];
  texType = 0;
  return true;
}

void		EditBox::update(const gdl::Clock &, gdl::Input &input, Map *board)
{
  int		key;

  key = SDLK_RIGHT;
  if (input.getKey(SDLK_LEFT) || input.getKey(SDLK_RIGHT) ||
      input.getKey(SDLK_UP) || input.getKey(SDLK_DOWN))
    {
      while (input.getKey(key, true) == false)
	++key;
      auto iterator = mvFcts.find(key);
      auto ptr = iterator->second;
      (this->*ptr)(board);
    }
  placeBlock(input, board);
  if (input.getKey(SDLK_a, true))
    prevTex();
  else if (input.getKey(SDLK_e, true))
    nextTex();
}

void		EditBox::draw(gdl::AShader &_shader, const gdl::Clock &_clock)
{
  box->drawEntity(_shader, _clock);
}

glm::vec3	EditBox::getPos(void)
{
  return (box->getPos());
}

void		EditBox::placeBlock(gdl::Input &input, Map *board)
{
  int		x;
  int		y;

  if (input.getKey(SDLK_SPACE, true))
    {
      x = box->getPos().x;
      y = box->getPos().y;
      board->getBoard()[y][x].pop_back();
      board->addElement(x, y, new Box(x, y, skin, box->getType()));
    }
}

void		EditBox::moveLeft(const Map *)
{
  if (box->getPos().x > 1)
  {
      blocks[0]->ftranslate(glm::vec3(-1, 0, 0));
      blocks[1]->ftranslate(glm::vec3(-1, 0, 0));
      blocks[2]->ftranslate(glm::vec3(-1, 0, 0));
  }
}

void		EditBox::moveRight(const Map *board)
{
  if (board->getWidth() > box->getPos().x)
    {
      blocks[0]->ftranslate(glm::vec3(1, 0, 0));
      blocks[1]->ftranslate(glm::vec3(1, 0, 0));
      blocks[2]->ftranslate(glm::vec3(1, 0, 0));
    }
}

void		EditBox::moveUp(const Map *board)
{

  if (board->getHeight() > box->getPos().y)
    {
      blocks[0]->ftranslate(glm::vec3(0, 1, 0));
      blocks[1]->ftranslate(glm::vec3(0, 1, 0));
      blocks[2]->ftranslate(glm::vec3(0, 1, 0));
    }
}

void		EditBox::moveDown(const Map *)
{
  if (box->getPos().y > 1)
    {
      blocks[0]->ftranslate(glm::vec3(0, -1, 0));
      blocks[1]->ftranslate(glm::vec3(0, -1, 0));
      blocks[2]->ftranslate(glm::vec3(0, -1, 0));
    }
}

void		EditBox::nextTex(void)
{
  if (texType == 2)
    texType = 0;
  else
    texType += 1;
  box = blocks[texType];
}

void		EditBox::prevTex(void)
{
  if (texType == 0)
    texType = 2;
  else
    texType -= 1;
  box = blocks[texType];
}
