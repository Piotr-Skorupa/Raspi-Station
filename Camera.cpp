#include "Camera.hpp"
#include "base64.h"

bool Camera::isRecording = false;

Camera::Camera()
    : logger_("Camera")
    {}

void Camera::makePhoto()
{
    try{
        logger_ << INFO << "Starting photo" << ENDL;
        system("raspistill --quality 10 --height 200 --width 200 -o last_photo.jpg"
            " --nopreview --exposure sports");
        logger_ << INFO << "Successful photo creation" << ENDL;
    }catch(std::exception const& e)
    {
        logger_ << ERROR << e.what() << ENDL;
    }
}

std::string Camera::recording()
{
    makePhoto();
    return imageToBase64();
}

std::string Camera::imageToBase64()
{
    std::ifstream image("last_photo.jpg");
    std::string strImage((std::istreambuf_iterator<char>(image)),
                 std::istreambuf_iterator<char>());

    return base64_encode(reinterpret_cast<const unsigned char*>(strImage.c_str()), strImage.length());
}