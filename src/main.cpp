#include <iostream>
#include  "pixeltoascii.hpp"
#include "checks.hpp"







int main(int argc,char * argv[])
{
    //variable used to store which flags are used
    int flags = 0;
    int pattern = 0;
    //video to open
    std::string file ;
    //result value to indicate exit code
    int result = 0;
    
    int option;
    //read options from terminal
    while ((option = getopt(argc, argv, "p:f:sS")) != -1)  // Corrected parentheses
    {
        switch (option)
        {
            //pattern 
            case 'p':
                pattern = strToInteger(optarg);
                break;

            case 'f':
                //check if path is empty and open default video if invalid path provided
                file = optarg;
                break;
            case 's':
                flags |= SOBEL_FLAG;
                break;
            case 'S':

                flags |= SHARPEN_FLAG;
                break;
                
        }
    }
    result = process_video(pattern,file,flags);
    return 0;
}


































