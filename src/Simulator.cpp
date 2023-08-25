#include "Simulator.h"
#include "math/Math.h"
#include "Parser.h"
#include "GL/glew.h"

void Simulator::sendDataToGpuBuffer(const Parser& parser)
{
  _vertexSize = parser._face.size();
  
  glGenVertexArrays(1, &_VAO);
  glBindVertexArray(_VAO);

  glGenBuffers(1, &_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, _VBO);
  glEnableVertexAttribArray(0);	
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);//size 열의 개수
  glBufferData(GL_ARRAY_BUFFER, sizeof(math::Vec4) * parser._face.size(), parser._face.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  std::vector<math::Vec3> colors;
  for (int i =0; i < _vertexSize; ++i)
  {
    math::Vec3 tmpColor;
    if (i % 3 == 0)
      tmpColor = math::Vec3(1,0,0);
    if (i % 3 == 1)
      tmpColor = math::Vec3(0,1,0);
    if (i % 3 == 2)
      tmpColor = math::Vec3(0,0,1);
    colors.push_back(tmpColor);
  }
  glGenBuffers(1, &_VCO);
  glBindBuffer(GL_ARRAY_BUFFER, _VCO);
  glEnableVertexAttribArray(1);	
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);//size 열의 개수
  glBufferData(GL_ARRAY_BUFFER, sizeof(math::Vec3) * colors.size(), colors.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

}

void Simulator::initialize(void)
{
  const std::string defualtPath = "/Users/schoe/Desktop/scope/resources/42.obj";
  Parser parser(defualtPath);

  parser.initialize();
  //getmtlVal
  sendDataToGpuBuffer(parser);
}

void Simulator::draw(void)
{
  glBindVertexArray(_VAO);
  glDrawArrays(GL_TRIANGLES, 0, _vertexSize);
  glBindVertexArray(0);
}

void Simulator::update(void)
{
    
}