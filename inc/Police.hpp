//
// Police.hpp for qwe in /home/quentin/bucket/bomberman
//
// Made by Quentin Richard
// Login   <quentin@epitech.net>
//
// Started on  Mon Jun  8 10:38:07 2015 Quentin Richard
// Last update Sun Jun 14 16:45:42 2015 Quentin Richard
//

#ifndef POLICE_H_
#define POLICE_H_

#include "GraphEngine.hpp"
#include "AEntity.hpp"

class Police : public AEntity
{
public:
  Police(GraphEngine *);
  ~Police();

public:
  void		strToScreen(const std::string &, glm::vec3);
  void		intToScreen(const int &) const;
  void		pushUv();
  void		initTexture();
  void		initMapFont();
  virtual bool	initGraph(void);
  virtual void	update(const gdl::Clock &_clock, gdl::Input &_input,
		       Map *board);
  virtual void	drawEntity(gdl::AShader &_Shader, const gdl::Clock &_clock);


private:
  GraphEngine			*win;
  std::map<char, gdl::Texture>	font;
  gdl::Texture			texA;
  gdl::Texture			texB;
  gdl::Texture			texC;
  gdl::Texture			texD;
  gdl::Texture			texE;
  gdl::Texture			texF;
  gdl::Texture			texG;
  gdl::Texture			texH;
  gdl::Texture			texI;
  gdl::Texture			texJ;
  gdl::Texture			texK;
  gdl::Texture			texL;
  gdl::Texture			texM;
  gdl::Texture			texN;
  gdl::Texture			texO;
  gdl::Texture			texP;
  gdl::Texture			texQ;
  gdl::Texture			texR;
  gdl::Texture			texS;
  gdl::Texture			texT;
  gdl::Texture			texU;
  gdl::Texture			texV;
  gdl::Texture			texW;
  gdl::Texture			texX;
  gdl::Texture			texY;
  gdl::Texture			texZ;
  gdl::Texture			tex1;
  gdl::Texture			tex2;
  gdl::Texture			tex3;
  gdl::Texture			tex4;
  gdl::Texture			tex5;
  gdl::Texture			tex6;
  gdl::Texture			tex7;
  gdl::Texture			tex8;
  gdl::Texture			tex9;
  gdl::Texture			tex0;
  gdl::Geometry			geometry;
  glm::vec3			pos;
  glm::vec3			rot;
  glm::vec3			scale;
};

#endif
