#pragma once

#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include "Logger.hpp"

class Camera
{
public:
    Camera();
    bool makePhoto();
    std::string imageToBase64();
    std::string recording();

    static bool isRecording;

private:
    Logger logger_;
};
