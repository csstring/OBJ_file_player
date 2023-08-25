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

void Parser::saveFace(const std::vector<std::string>& v)
{
  if (v.size() <= 3)
  {
    std::cerr << "face size error "<< std::endl;
    exit(1);
  }

  for (int i = 1; i <= v.size() - 3; ++i)
  {
    uint32 index1 = std::stoi(v[i]) - 1;
    uint32 index2 = std::stoi(v[i+1]) - 1;
    uint32 index3 = std::stoi(v[i+2]) - 1;
    math::Vec4 t1 = _vertecies[index1];
    math::Vec4 t2 = _vertecies[index2];
    math::Vec4 t3 = _vertecies[index3];
    _face.push_back(t1);
    _face.push_back(t2);
    _face.push_back(t3);
  }
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
  if (_mtlFilePath.empty() == true)
  {
    std::cerr << "mtl file path fail" << std::endl;
    exit(1);
  }

  // std::ifstream mtlIfs(_mtlFilePath);
  // if (mtlIfs.is_open() == false)
  // {
  //   std::cerr << "mtl file path fail" << std::endl;
  //   exit(1);
  // }

  // parseMtl(mtlIfs);
}