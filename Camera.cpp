#include "Camera.hpp"
#include "base64.h"

bool Camera::isRecording = false;

Camera::Camera()
    : logger_("Camera")
    {}

bool Camera::makePhoto()
{
    logger_ << INFO << "Starting photo" << ENDL;
    int systemResult = system("raspistill --quality 10 --height 200 --width 200 -o last_photo.jpg --timeout 1");

    if (systemResult != 0)
    {
        logger_ << ERROR << "Camera is disconnected" << ENDL;
        Camera::isRecording = false;
        return false;
    }

    logger_ << INFO << "Successful photo creation" << ENDL;
    return true;
}

std::string Camera::recording()
{
    if (!makePhoto())
    {
        logger_ << ERROR << "Sending camera error..." << ENDL;
        return std::string("CAMERA_ERROR");
    }
    return imageToBase64();
}

std::string Camera::imageToBase64()
{
    std::ifstream image("last_photo.jpg");
    std::string strImage((std::istreambuf_iterator<char>(image)),
                 std::istreambuf_iterator<char>());

    return base64_encode(reinterpret_cast<const unsigned char*>(strImage.c_str()), strImage.length());
}