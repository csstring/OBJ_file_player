#pragma once
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ostream>
#include <cmath>
#include "math/Mat3.h"
#include "math/Mat4.h"
#include "math/Quat.h"
#include "math/Vec3.h"
#include "math/Vec4.h"
#include "math/Vec2.h"
#include <filesystem>
#define GL_SILENCE_DEPRECATION
typedef signed char         int8;
typedef signed short        int16;
typedef signed int          int32;
typedef signed long         int64;
typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;
typedef unsigned long       uint64;        

const float OVERLAPTIME = 200;
class Noncopyable
{
    public:
        inline ~Noncopyable(void){}
    protected:
        inline Noncopyable(void){}
    private:
        Noncopyable(const Noncopyable&) = delete;
        Noncopyable(Noncopyable&) = delete;
        Noncopyable& operator=(const Noncopyable&) = delete;
        Noncopyable& operator=(Noncopyable&) = delete;
};

//debug
void ft_assert(const std::string& exec);

//utility
std::vector<std::string> ft_split(const std::string& str);
inline std::chrono::steady_clock::time_point getCurTimePoint(void)
{
    return std::chrono::steady_clock::now();
}

inline std::chrono::steady_clock::time_point getAfterTimePoint(float time)
{
    return std::chrono::steady_clock::now() + std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::duration<double>(time/1000));
}

inline float getMilisecondTime(const std::chrono::steady_clock::time_point& curTime, const std::chrono::steady_clock::time_point& _prevTime)
{
    std::chrono::milliseconds millisecond = std::chrono::duration_cast<std::chrono::milliseconds>(curTime - _prevTime);
    return millisecond.count();
}