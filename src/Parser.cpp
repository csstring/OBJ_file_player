#include "Parser.h"

void Parser::saveVertex(const std::vector<std::string>& v)
{
  if (v.size() != 4)
  {
    std::cerr << "vertex size error "<< std::endl;
    exit(1);
  }
  math::Vec4 vertex(std::stof(v[1]), std::stof(v[2]), std::stof(v[3]), 1);
  _vertecies.push_back(vertex);
}

void Parser::saveUV(const std::vector<std::string>& v)
{
  if (v.size() != 3)
  {
    std::cerr << "UV size error "<< std::endl;
    exit(1);
  }
  math::Vec2 vertex(std::stof(v[1]), std::stof(v[2]));
  _uv.push_back(vertex);
}

void Parser::saveNormal(const std::vector<std::string>& v)
{
  if (v.size() != 4)
  {
    std::cerr << "normal size error "<< std::endl;
    exit(1);
  }
  math::Vec3 vertex(std::stof(v[1]), std::stof(v[2]), std::stof(v[3]));
  _normal.push_back(vertex);
}
/*
1
1/1/1
1//1
1/1
*/
void Parser::saveIndex(const std::vector<std::string>& v, uint32 count)
{
  _uvIndex.clear();
  _normalIndex.clear();
  _posIndex.clear();

  uint32 Case;
  if (_uv.empty() == true && _normal.empty() == true)
    Case = 0;
  else if (_uv.empty() == false && _normal.empty() == false)
    Case = 1;
  else if (_uv.empty() == true && _normal.empty() == false)
    Case = 2;
  else if (_uv.empty() == false && _normal.empty() == true)
    Case = 3;
  else
  {
    std::cerr << "face format error\n";
    exit(1);
  }

  for (int i =1; i < count; ++i)
  {
    uint32 posi, uvi, normali, matches;

    switch (Case)
    {
    case 0:
      matches = sscanf(v[i].c_str(), "%d", &posi);
      if (matches != 1){
        std::cerr << "face format error\n";
        exit(1);
      }
      _posIndex.push_back(posi - 1);
      break;
    case 1:
      matches = sscanf(v[i].c_str(), "%d/%d/%d", &posi, &uvi, &normali);
      if (matches != 3){
        std::cerr << "face format error\n";
        exit(1);
      }
      _posIndex.push_back(posi - 1);
      _uvIndex.push_back(uvi - 1);
      _normalIndex.push_back(normali - 1);
      break;
    case 2:
      matches = sscanf(v[i].c_str(), "%d//%d", &posi, &normali);
      if (matches != 2){
        std::cerr << "face format error\n";
        exit(1);
      }
      _posIndex.push_back(posi - 1);
      _normalIndex.push_back(normali - 1);
      break;
    case 3:
      matches = sscanf(v[i].c_str(), "%d/%d", &posi, &uvi);
      if (matches != 2){
        std::cerr << "face format error\n";
        exit(1);
      }
      _posIndex.push_back(posi - 1);
      _uvIndex.push_back(uvi - 1);
      break;
    }
  }
}

void Parser::saveTriangleVertex(const std::vector<std::string>& v)
{
  if (_vertecies.empty() == false)
  {
    _facePos.push_back(_vertecies[_posIndex[0]]);
    _facePos.push_back(_vertecies[_posIndex[1]]);
    _facePos.push_back(_vertecies[_posIndex[2]]);
  }
  if (_uv.empty() == false)
  {
    _faceUV.push_back(_uv[_uvIndex[0]]);
    _faceUV.push_back(_uv[_uvIndex[1]]);
    _faceUV.push_back(_uv[_uvIndex[2]]);
  }
  if (_normal.empty() == false)
  {
    _faceNormal.push_back(_normal[_normalIndex[0]]);
    _faceNormal.push_back(_normal[_normalIndex[1]]);
    _faceNormal.push_back(_normal[_normalIndex[2]]);
  }
}

void Parser::saveQuadVertex(const std::vector<std::string>& v)
{
  saveTriangleVertex(v);
  if (_vertecies.empty() == false)
  {
    _facePos.push_back(_vertecies[_posIndex[2]]);
    _facePos.push_back(_vertecies[_posIndex[3]]);
    _facePos.push_back(_vertecies[_posIndex[0]]);
  }
  if (_uv.empty() == false)
  {
    _faceUV.push_back(_uv[_uvIndex[2]]);
    _faceUV.push_back(_uv[_uvIndex[3]]);
    _faceUV.push_back(_uv[_uvIndex[0]]);
  }
  if (_normal.empty() == false)
  {
    _faceNormal.push_back(_normal[_normalIndex[2]]);
    _faceNormal.push_back(_normal[_normalIndex[3]]);
    _faceNormal.push_back(_normal[_normalIndex[0]]);
  }
}

void Parser::saveFace(const std::vector<std::string>& v)
{
  if (v.size() <= 3)
  {
    std::cerr << "face size error "<< std::endl;
    exit(1);
  }
  saveIndex(v, v.size());
  if (v.size() == 4)
    saveTriangleVertex(v);
  else if (v.size() == 5)
    saveQuadVertex(v);
}

void Parser::parseObj(std::ifstream& ifs)
{
  std::string buffer;
  std::vector<std::string> v;

  while (ifs.good())
  {
    std::getline(ifs, buffer);
    v = ft_split(buffer);

    if (v.empty() == true)
      break;
    
    if (v[0] == "#")
      continue;
    else if (v[0] == "mtllib")
    {
      std::cout <<"mtl check" << std::endl;
      std::cout << v[1] << std::endl;
      _mtlFilePath = v[1];
    }
    else if (v[0] == "o")
    {}
    else if (v[0] == "v")
      saveVertex(v);
    else if (v[0] == "vt")
      saveUV(v);
    else if (v[0] == "vn")
      saveNormal(v);
    else if (v[0] == "s")
    {}
    else if (v[0] == "f")
      saveFace(v);
  }
}

void Parser::parseMtl(std::ifstream& ifs) //to do
{

}

void Parser::initialize(void)
{
  std::ifstream ifs(_objFilePath);

  if (ifs.is_open() == false)
  {
    std::cerr << "Obj file path fail" << std::endl;
    exit(1);
  }

  parseObj(ifs);
  // if (_mtlFilePath.empty() == true)
  // {
  //   std::cerr << "mtl file path fail" << std::endl;
  //   exit(1);
  // }

  // std::ifstream mtlIfs(_mtlFilePath);
  // if (mtlIfs.is_open() == false)
  // {
  //   std::cerr << "mtl file path fail" << std::endl;
  //   exit(1);
  // }

  // parseMtl(mtlIfs);
}