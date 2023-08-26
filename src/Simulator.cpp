#include "Simulator.h"
#include "math/Math.h"
#include "Parser.h"
#include "GL/glew.h"
#include <random>
#include "DDSLoder.h"
#include <algorithm>

void Simulator::colorBlendingStart(NUMINPUT input)
{
  if (_blendingRatio != 1)
    return;

  _numInput = NUMINPUT::DEFAULT;
  _blendingRatio = 0;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis(0.0, 1.0);
  float random1 = dis(gen);
  float random2 = dis(gen);
  float random3 = dis(gen);
  _nextColor = math::Vec3(random1, random2,random3);
}

void Simulator::moveObjectThreeAxis(math::Vec3 move)
{
  _worldTranslate = math::translate(_worldTranslate, move);
}

void Simulator::moveToCenter(Parser& parser)
{
  float maxX,maxY,maxZ,minX,minY,minZ;
  maxX = parser._vertecies[0].x;
  minX = parser._vertecies[0].x;
  maxY = parser._vertecies[0].y;
  minY = parser._vertecies[0].y;
  maxZ = parser._vertecies[0].z;
  minZ = parser._vertecies[0].z;

  for (const auto& it : parser._vertecies)
  {
    if (it.x > maxX)
      maxX = it.x;
    if (it.x < minX)
      minX = it.x;
    if (it.y > maxY)
      maxY = it.y;
    if (it.y < minY)
      minY = it.y;
    if (it.z > maxZ)
      maxZ = it.z;
    if (it.z < minZ)
      minZ = it.z;
  }
  math::Vec4 center((maxX - minX)/2, (maxY - minY)/2,(maxZ - minZ)/2,0);
  for (auto& it : parser._facePos)
    it -= center;
}

void Simulator::sendDataToGpuBuffer(const Parser& parser)
{
  _vertexSize = parser._facePos.size();
  
  glGenVertexArrays(1, &_VAO);
  glBindVertexArray(_VAO);

  glGenBuffers(1, &_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, _VBO);
  glEnableVertexAttribArray(0);	
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);//size 열의 개수
  glBufferData(GL_ARRAY_BUFFER, sizeof(math::Vec4) * parser._facePos.size(), parser._facePos.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  std::vector<math::Vec3> colors;
  colors.resize(_vertexSize, math::Vec3(1,0,1));
  _curColor = math::Vec3(1,0,1);
  glGenBuffers(1, &_VCO);
  glBindBuffer(GL_ARRAY_BUFFER, _VCO);
  glEnableVertexAttribArray(1);	
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);//size 열의 개수
  glBufferData(GL_ARRAY_BUFFER, sizeof(math::Vec3) * colors.size(), colors.data(), GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glGenBuffers(1, &_uvID);
  glBindBuffer(GL_ARRAY_BUFFER, _uvID);
  glEnableVertexAttribArray(2);	
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);//size 열의 개수
  glBufferData(GL_ARRAY_BUFFER, sizeof(math::Vec2) * parser._faceUV.size(), parser._faceUV.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glGenBuffers(1, &_normalID);
  glBindBuffer(GL_ARRAY_BUFFER, _normalID);
  glEnableVertexAttribArray(3);	
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);//size 열의 개수
  glBufferData(GL_ARRAY_BUFFER, sizeof(math::Vec3) * parser._faceNormal.size(), parser._faceNormal.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

}

math::Vec3 Simulator::blendingColor(float delta)
{
  _blendingRatio += delta;
  if (_blendingRatio >= 1.0f)
  {
    _blendingRatio = 1;
    _curColor = _nextColor;
  }

  return math::mix(_curColor, _nextColor, _blendingRatio);
}

void Simulator::initialize(void)
{
  const std::string defualtPath = "/Users/schoe/Desktop/scope/resources/suzanne.obj";
  const std::string defualtTexturePath = "/Users/schoe/Desktop/scope/resources/uvmap.DDS";
  Parser parser(defualtPath);
  DDSLoder textureLoder(defualtTexturePath);
  
  _worldTranslate = math::Mat4(1.0f);
  parser.initialize();
  _textureID = textureLoder.loadDDS();
  
  if (_textureID == 0)
  {
    std::cerr << "texture file error\n";
    exit(1);
  }
  sendDataToGpuBuffer(parser);
}

void Simulator::draw(void)
{
  glBindTexture(GL_TEXTURE_2D, _textureID);
  glBindVertexArray(_VAO);
  glDrawArrays(GL_TRIANGLES, 0, _vertexSize);
  glBindVertexArray(0);
}

void Simulator::update(float delta)
{
  math::Vec3 color;
  std::vector<math::Vec3> colors;

  if (_blendingRatio == 1)
    color = _curColor;
  else 
    color = blendingColor(delta);

  colors.resize(_vertexSize, color);
  glBindVertexArray(_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, _VCO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(math::Vec3) * colors.size(), colors.data(), GL_DYNAMIC_DRAW);;
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}