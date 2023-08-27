#pragma once
#include "Common.h"
#include "fstream"
struct MtlStruct;
class Parser
{
  private:
    std::string _objFilePath;
    std::string _mtlFilePath;
    std::vector<uint32> _posIndex, _uvIndex, _normalIndex, _faceIndex;
    uint32 _Case;

  public:
    std::vector<math::Vec4> _vertices;
    std::vector<math::Vec2> _uv;
    std::vector<math::Vec3> _normal;
    std::vector<math::Vec4> _facePos;
    std::vector<math::Vec2> _faceUV;
    std::vector<math::Vec3> _faceNormal;

  private:
    void parseObj(std::ifstream& ifs);
    void parseMtl(std::ifstream& ifs, MtlStruct& mtlStruct);

    void saveVertex(const std::vector<std::string>& v);
    void saveUV(const std::vector<std::string>& v);
    void saveNormal(const std::vector<std::string>& v);
    void saveFace(const std::vector<std::string>& v);
    void saveTriangleVertex(const std::vector<std::string>& v);
    void saveQuadVertex(const std::vector<std::string>& v);
    void saveIndex(const std::vector<std::string>& v,uint32 count);
    void saveCase(void);

    void generateUV(void);
    void generateNormal(void);

  public:
    Parser(const std::string& filePath) : _objFilePath(filePath){};
    ~Parser(){};
    void initialize(MtlStruct& mtlStruct);
};
