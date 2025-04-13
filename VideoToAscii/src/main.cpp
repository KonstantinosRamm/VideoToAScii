#include <iostream>
#include  "pixeltoascii.hpp"
#include "checks.hpp"







int main(int argc,char * argv[])
{
    //variable used to store which flags are used
    int flags = 0;
    int pattern = 0;
    //video to open
    std::string file = DEFAULT_PATH;
    //result value to indicate exit code
    int result = 0;
    
    int option;
    //read options from terminal
    while ((option = getopt(argc, argv, "p:f:sSg")) != -1)  // Corrected parentheses
    {
        switch (option)
        {
            case 'p'://pattern
                pattern = strToInteger(optarg);
                break;

            case 'f'://define file
                file = optarg;
                break;
                
            case 's'://sobel
                flags |= SOBEL_FLAG;
                break;

            case 'S'://sharpening
                flags |= SHARPEN_FLAG;
                break;

            case 'g'://gaussian blur
                flags |= GAUSSIAN_BIT;
                break;        
        }
    }
    result = process_video(pattern,file,flags);
    return result;
}
