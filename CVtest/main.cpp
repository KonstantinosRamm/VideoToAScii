#include <opencv2/opencv.hpp>



int main(void)
{
    cv::Mat image = cv::imread("wall.jpg");

    if (image.empty())
    {
        std::cerr << "Error could not open image!" << std::endl;
        return -1;
    }

    cv::Mat grayImage;
    cv::cvtColor(image,grayImage,cv::COLOR_BGR2GRAY);

    //display original and the modified image
    cv::imshow("Original image",image);
    cv::imshow("Modified image",grayImage);
    //wait user input to exit

    cv::waitKey(0);

    return 0;

    
}