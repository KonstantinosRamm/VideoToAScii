#include <iostream>
#include <opencv2/highgui.hpp>
#include <chrono>
#include <thread>


int main(int argc,char * argv[])
{
    //read video (hardcoded for now to sample/sample.txt)
    cv::VideoCapture video("sample/sample.mp4");
    if(!video.isOpened())
    {
        std::cerr << "[ERROR] opening video\n";
        return -1;
    }


    cv::Mat frame;
    //get fps
    double fps = video.get(cv::CAP_PROP_FPS);

    video.release();
    return 0;
}

