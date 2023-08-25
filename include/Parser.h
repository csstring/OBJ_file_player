#pragma once
#include "Common.h"
#include "fstream"
class Parser
{
  private:
    std::string _objFilePath;
    std::string _mtlFilePath;
    
  public:
    std::vector<math::Vec4> _vertecies;
    std::vector<math::Vec4> _face;
    float _ns;
    math::Vec3 _ka;
    math::Vec3 _kd;
    math::Vec3 _ks;
    math::Vec3 _ni;
    float _d;
    uint8 _illum;

  private:
    void parseObj(std::ifstream& ifs);
    void parseMtl(std::ifstream& ifs);
    void saveVertex(const std::vector<std::string>& v);
    void saveFace(const std::vector<std::string>& v);
    void saveTriangleVertex(const std::vector<std::string>& v);
    void saveQuadVertex(const std::vector<std::string>& v);
  public:
    Parser(const std::string& filePath) : _objFilePath(filePath){};
    ~Parser(){};
    void initialize(void);
};
