#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <thread>
#include <string>
#include <cstdlib>
#include <sys/ioctl.h> // ioctl and struct winsize
#include <unistd.h> // for STDOUT_FILENO
#include <getopt.h>
#include "ansi.hpp"
#include "pixeltoascii.hpp"
#include "checks.hpp"
#include "flags.hpp"

#define DEFAULT_PATH "sample/sample.mp4"


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
 * @param flags checks if sobel filter flag enabled
 */
void sobelOperator(cv::Mat & frame,int flags);


/**
 * @brief applies sharpening to the currently processed frame
 * @param frame current frame to be processed 
 * @param flags checks if  sharpen flag enabled
 */

void SharpeningFilter(cv::Mat & frame,int flags);


/**
 * @brief applies Gaussian Blur to the currently processed frame
 * @param frame current frame to process
 * @param flags checks if Gaussian flag enabled
 */

 void GaussianBlur(cv::Mat & frame,int flags);



/**
 * @brief  video process function to convert to ascii
 * @param pattern pattern to choose .If invalid number passed as argument it will return pattern 1 (index 0)
 * @param file image to open
 * @param flags determine flags used to use appropriate filters
 * @return 0 if all operations succeeded else -1
 */
int process_video(int pattern = 0,std::string file = "sample/sample.mp4",int flags = 0);




/**
 * @brief wrapper that applies the filters to each frame 
 * @param frame current frame to be processed
 * @param flags determine the flags used to use the appropriate filters
 */

 void applyFilters(cv::Mat & frame, int flags);





