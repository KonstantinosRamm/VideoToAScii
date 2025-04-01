#pragma once
#include <string>
#include <opencv2/opencv.hpp>


/**
 * @brief  function to calculate current pixels value and 
 * convert it into ascii character
 * @param pixelValue current pixels value
 * @param ascii_index used to check which pattern to use default = 0
 * @return character based on current pixel
 */
char pixelToAscii(int pixelValue,int ascii_index = 0);

/**
 * @brief converts current frame into an ascii string 
 * @param frame current frame to be processed
 * @param pattern pattern defined by user through argv (optional)
 * @return the frame converted into string
 */
std::string convertToAscii(const cv::Mat& frame,int pattern);


/**
 * @brief applies sobel operator to the currently processed frame but first it checks it the flag for sobel operator is already activated through argv
 * @param frame current frame to be processed 
 * @param sobel checks if sobel filter activated 
 */
void sobelOperator(cv::Mat & frame,bool sobel);
