#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <thread>
#include <string>
#include "pixeltoascii.hpp"



int main(int argc,char * argv[])
{
    //read video (hardcoded for now to sample/sample.txt)
    cv::VideoCapture video("sample/sample.mp4");
    if(!video.isOpened())
    {
        std::cerr << "[ERROR] opening video\n";
        return -1;
    }

    //dimentions 
    int width = 100;
    int height = 40;
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
                int pixelValue = pixelToAscii(resized_mat.at<uchar>(i,j));
                frame_ascii += pixelValue;
            }
            frame_ascii += "\n";
        }

        //move the cursor and update pixels for more smooth transitions
        std::cout << "\033[H";
        std::cout << frame_ascii;
        //wait for some time between each frame and clear screen for next iteration
        std::this_thread::sleep_for(std::chrono::milliseconds( frame_ms_duration));



    }

    cv::waitKey();
    video.release();

    return 0;
}

