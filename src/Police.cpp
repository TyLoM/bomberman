//
// Police.cpp for qwe in /home/quentin/bucket/bomberman
//
// Made by Quentin Richard
// Login   <quentin@epitech.net>
//
// Started on  Mon Jun  8 10:37:25 2015 Quentin Richard
// Last update Sun Jun 14 17:01:36 2015 Quentin Richard
//

#include "Police.hpp"
#include "Error.hpp"

Police::Police(GraphEngine *_win) : AEntity(0, 0, VOID_BLOCK)

{
  win = _win;
}

Police::~Police()
{
}

void	Police::initTexture()
{
  texA.load("./assets/prototypes/A.tga");
  texB.load("./assets/prototypes/B.tga");
  texC.load("./assets/prototypes/C.tga");
  texD.load("./assets/prototypes/D.tga");
  texE.load("./assets/prototypes/E.tga");
  texF.load("./assets/prototypes/F.tga");
  texG.load("./assets/prototypes/G.tga");
  texH.load("./assets/prototypes/H.tga");
  texI.load("./assets/prototypes/I.tga");
  texJ.load("./assets/prototypes/J.tga");
  texK.load("./assets/prototypes/K.tga");
  texL.load("./assets/prototypes/L.tga");
  texM.load("./assets/prototypes/M.tga");
  texN.load("./assets/prototypes/N.tga");
  texO.load("./assets/prototypes/O.tga");
  texP.load("./assets/prototypes/P.tga");
  texQ.load("./assets/prototypes/Q.tga");
  texR.load("./assets/prototypes/R.tga");
  texS.load("./assets/prototypes/S.tga");
  texT.load("./assets/prototypes/T.tga");
  texU.load("./assets/prototypes/U.tga");
  texV.load("./assets/prototypes/V.tga");
  texW.load("./assets/prototypes/W.tga");
  texX.load("./assets/prototypes/X.tga");
  texY.load("./assets/prototypes/Y.tga");
  texZ.load("./assets/prototypes/Z.tga");
  tex0.load("./assets/prototypes/0.tga");
  tex1.load("./assets/prototypes/1.tga");
  tex2.load("./assets/prototypes/2.tga");
  tex3.load("./assets/prototypes/3.tga");
  tex4.load("./assets/prototypes/4.tga");
  tex5.load("./assets/prototypes/5.tga");
  tex6.load("./assets/prototypes/6.tga");
  tex7.load("./assets/prototypes/7.tga");
  tex8.load("./assets/prototypes/8.tga");
  tex9.load("./assets/prototypes/9.tga");
}

void	Police::initMapFont()
{
  // initTexture();
  // font['A'] = texA;
  // font['B'] = texB;
  // font['C'] = texC;
  // font['D'] = texD;
  // font['E'] = texE;
  // font['F'] = texF;
  // font['G'] = texG;
  // font['H'] = texH;
  // font['I'] = texI;
  // font['J'] = texJ;
  // font['K'] = texK;
  // font['L'] = texL;
  // font['M'] = texM;
  // font['N'] = texN;
  // font['O'] = texO;
  // font['P'] = texP;
  // font['Q'] = texQ;
  // font['R'] = texR;
  // font['S'] = texS;
  // font['T'] = texT;
  // font['U'] = texU;
  // font['V'] = texV;
  // font['W'] = texW;
  // font['X'] = texX;
  // font['Y'] = texY;
  // font['Z'] = texZ;
  // font['0'] = tex0;
  // font['1'] = tex1;
  // font['2'] = tex2;
  // font['3'] = tex3;
  // font['4'] = tex4;
  // font['5'] = tex5;
  // font['6'] = tex6;
  // font['7'] = tex7;
  // font['8'] = tex8;
  // font['9'] = tex9;
}

void	Police::strToScreen(const std::string &str, glm::vec3 _pos)
{
  const char *arr = str.c_str();

  pos = _pos;
  for (int step = 0; arr[step]; step++)
    {
      drawEntity(*(win->getShader()), win->getClock());
      // pos += glm::vec3(0.01, 0, 0);
    }
}

bool		Police::initGraph()
{
  if (texA.load("./assets/prototypes/A.tga") == false)
    throw Error("Failed to load Cube texture");

  geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  pushUv();
  geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  pushUv();
  geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  pushUv();
  geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  pushUv();
  geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
  geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
  geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  pushUv();
  geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  pushUv();
  geometry.build();
  return (true);
}

void		Police::pushUv()
{
  geometry.pushUv(glm::vec2(0.0f, 0.0f));
  geometry.pushUv(glm::vec2(1.0f, 0.0f));
  geometry.pushUv(glm::vec2(1.0f, 1.0f));
  geometry.pushUv(glm::vec2(0.0f, 1.0f));
}

void		Police::update(const gdl::Clock &, gdl::Input &, Map *)
{
  if (getType() == CURSOR1 || getType() == CURSOR2)
    rot += glm::vec3(0, 0, 1);
}

void		Police::drawEntity(gdl::AShader &_shader, const gdl::Clock &)
{
  texA.bind();
  geometry.draw(_shader, getTransformation(), GL_QUADS);
}



void	Police::intToScreen(const int &) const
{
}
