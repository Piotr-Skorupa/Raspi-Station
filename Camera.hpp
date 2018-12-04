#pragma once

#include <cstdio>
#include <iostream>

namespace Camera
{

void makePhoto()
{
    try{
        system("raspistill -o last_photo.jpg");
    }catch(std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

} // namespace Camera