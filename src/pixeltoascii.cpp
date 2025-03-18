#include "pixeltoascii.hpp"


char pixelToAscii(int pixelValue)
{
    
    const std::string asciiChars = "@%#*+=-:. ";

    int index = pixelValue * (asciiChars.size() -1) / 255;
    return asciiChars[index];
}