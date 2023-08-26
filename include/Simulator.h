#pragma once
#include "Common.h"
#include "EnumHeader.h"
class Parser;
class Simulator : Noncopyable
{
    private:
        void sendDataToGpuBuffer(const Parser& parser);
        void moveToCenter(Parser& parser);
        math::Vec3 blendingColor(float delta);
        uint32 _VAO, _VBO, _VCO, _textureID, _uvID, _normalID;
        uint32 _vertexSize;
        math::Vec3 _curColor;
        math::Vec3 _nextColor;
        float      _blendingRatio = 1;

    private:
        float _ns;
        math::Vec3 _ka;
        math::Vec3 _kd;
        math::Vec3 _ks;
        math::Vec3 _ni;
        float _d;
        uint8 _illum;

    public:
        math::Mat4 _worldTranslate;
        NUMINPUT _numInput;
        Simulator(){}
        ~Simulator(){}
        
        void initialize(void);
        void update(float delta);
        void draw(void);
        void colorBlendingStart(NUMINPUT input);
        void moveObjectThreeAxis(math::Vec3 move);
};

// std::ostream& operator<<(std::ostream& os, const std::pair<Animation*, TimeNode>& ref);