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
                                                                      "'                                 .:-=+*#%@!",

    
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




std::string convertToAscii(const cv::Mat& frame,int pattern)
{
    
    int rows = frame.rows;
    int cols = frame.cols;
    std::string frame_ascii;
        //read each pixel and print its ascii value and print to terminal
    for(int  i = 0; i < rows; i++)
    {
        for(int j = 0 ; j < cols; j++)
        {
            int pixelValue = pixelToAscii(frame.at<uchar>(i,j),pattern);
            frame_ascii += pixelValue;
        }
        frame_ascii += "\n";
    }

    return frame_ascii;
}





void sobelOperator(cv::Mat & frame,bool sobel)
{
    //calculate sobel operator
    if(sobel)
    {
        cv::Mat grad_x,grad_y,sobel_output;
        //Compute x gradient
        cv::Sobel(frame, grad_x, CV_64F, 1, 0, 3);
        //Compute y gradient
        cv::Sobel(frame, grad_y, CV_64F, 0, 1, 3);
            //Compute magnitude
        cv::magnitude(grad_x, grad_y, sobel_output);

        //normalize to 8-bit for conversion to ascii(map values to range 0-255)
        //and store the output to resized_mat
        //cv::NORM_MINMAX range based formula
        cv::normalize(sobel_output, frame, 0, 255, cv::NORM_MINMAX, CV_8U);
    }
 }