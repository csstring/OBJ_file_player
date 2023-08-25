#pragma once

#include "Common.h"

class Parser;
class Simulator : Noncopyable
{
    private:
        void sendDataToGpuBuffer(const Parser& parser);
        uint32 _VAO, _VBO, _VCO;
        uint32 _vertexSize;
    private:
        float _ns;
        math::Vec3 _ka;
        math::Vec3 _kd;
        math::Vec3 _ks;
        math::Vec3 _ni;
        float _d;
        uint8 _illum;
    public:
        Simulator(){}
        ~Simulator(){}
        
        void initialize(void);
        void update(void);
        void draw(void);
};

// std::ostream& operator<<(std::ostream& os, const std::pair<Animation*, TimeNode>& ref);