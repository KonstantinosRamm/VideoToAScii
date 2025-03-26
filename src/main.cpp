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
#include "options.hpp"

/**
 * @brief  video process function to convert to ascii
 * @param pattern pattern to choose .If invalid number passed as argument it will return pattern 1 (index 0)
 * @return 0 if all operations succeeded else -1
 */
int process_video(int pattern = 0);


int main(int argc,char * argv[])
{
    //pattern to choose from for ascii display style
    int pattern = 0;


    int option;
    //read options from terminal
    while ((option = getopt(argc, argv, "p:")) != -1)  // Corrected parentheses
    {
        switch (option)
        {
            case 'p':
                pattern = strToInteger(optarg);
                break;
        }
    }
    
    process_video(pattern);
    return 0;
}

























int process_video(int pattern)
{
    //read video (hardcoded for now to sample/sample.txt)
    cv::VideoCapture video("sample/sample.mp4");
    if(!video.isOpened())
    {
        std::cerr << "[ERROR] opening video\n";
        return -1;
    }
    //store terminal window dimensions
    struct winsize size;
    

    //dimentions  
    int width = 0 ;
    int height  = 0;
    cv::Mat frame,grayScale,resized_mat;
    //get fps 
    double fps = video.get(cv::CAP_PROP_FPS);

    //check if open cv read fps 
    if(fps == 0)
    {
        std::cerr << "[ERROR] could not read fps" << std::endl;
        return -1;
    }
    int frame_ms_duration = static_cast<int>(1000 / fps);

    while(true)
    {

        //get starting time
        auto start_time = std::chrono::high_resolution_clock::now();
        //read current dimentions in order to resize accordingly
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        if (size.ws_row != height || size.ws_col != width)
        {

            height = size.ws_row;
            width = size.ws_col;
            //clear screen  and reset cursor to avoid messing up character printing 
            system("clear");  

        }

        video >> frame;
        //check for the end of video
        if(frame.empty())
        {
            break;
        }
        std::string frame_ascii;
        //covert frame into grayscale
        cv::cvtColor(frame, grayScale, cv::COLOR_BGR2GRAY);
        cv::resize(grayScale,resized_mat, cv::Size(width,height), 0, 0, cv::INTER_CUBIC);
        
        int rows = resized_mat.rows;
        int cols = resized_mat.cols;

        //read each pixel and print its ascii value and print to terminal
        for(int  i = 0; i < rows; i++)
        {
            for(int j = 0 ; j < cols; j++)
            {
                int pixelValue = pixelToAscii(resized_mat.at<uchar>(i,j),pattern);
                frame_ascii += pixelValue;
            }
            frame_ascii += "\n";
        }

        //move the cursor and update pixels for more smooth transitions
        std::cout << RESET_CURSOR;
        std::cout << frame_ascii;

        auto end_time = std::chrono::high_resolution_clock::now(); // end time 

        //calculate processing time
       auto processing_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        long sleep_time = frame_ms_duration - processing_time;

        //check if we need to wait before each frame
        if(sleep_time > 0)
        {
             std::this_thread::sleep_for(std::chrono::milliseconds( sleep_time));
        }



    }

    video.release();
    cv::waitKey();

    return 0;
}