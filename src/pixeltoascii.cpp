#include "pixeltoascii.hpp"


char pixelToAscii(int pixelValue,int ascii_index)
{
    
    const std::string asciiChars[] = {  
                                                                    //gradient
                                                                     "@%#*+=-:. ",
                                                                     //gradient reverse
                                                                      " .:-=+*#%@",
                                                                      //more gradient
                                                                      "@%#*+=-:.                                  '",
                                                                      //more gradient reverse
                                                                      "'                                 .:-=+*#%@!"


    
                                                                     
                                                                        



    };
    //ensure ascii_index is not out of bonds of string  array
    if(ascii_index < 0 || ascii_index >= sizeof(asciiChars) / sizeof(asciiChars[0]))
    {
        ascii_index = 0;
    }

    std::string pattern = asciiChars[ascii_index];

    int index = pixelValue * (pattern.size() -1) / 255;
    return pattern[index];
}