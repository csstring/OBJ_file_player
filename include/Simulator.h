#pragma once

#include "Common.h"

class Simulator : Noncopyable
{
    private:

    public:
        Simulator(){}
        ~Simulator(){}
        
        void initialize(void);
        void update(void);
        void draw(void);
};

// std::ostream& operator<<(std::ostream& os, const std::pair<Animation*, TimeNode>& ref);