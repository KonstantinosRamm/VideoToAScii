#include "pixeltoascii.hpp"


char pixelToAscii(int pixelValue,int ascii_index)
{
    
    const std::string asciiChars[] = {  

                                                                     
        //default
        "@%#*+=-:. ",

        " .:-=+*#%@",

        "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,^`'.",

        " .'`^,:;Il!i><~+_-?][}{1)(|/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$",

        "@%#*+=-:.                                  '",

        "'                                 .:-=+*#%@!",

        ".',-^_~()[]{}<>|/\\",

        "\\/|><}{}][)(~_^-,'.)]",

        "ZYXWVUTSRQPONMLKJIHGFEDCBA",

        "ABCDEFGHIJKLMNOPQRSTUVWXYZ",

        "@B8&$%#*+=-:. ,",

        ", .:-=+*#%$&8B@"
    
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


void sobelOperator(cv::Mat & frame,int flags)
{
    //calculate sobel operator
    if(flags & SOBEL_FLAG)
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

void SharpeningFilter(cv::Mat & frame,int flags)
{
    //constructor of kernel
    cv::Mat kernel = (cv::Mat_<float>(3, 3) << 
      0,   -1,    0,
    -1,     5,   -1,
      0,   -1,    0);



    if(flags & SHARPEN_FLAG)
    {
        cv::filter2D(frame,frame,frame.depth(),kernel);
    }

                        
}



void GaussianBlur(cv::Mat & frame,int flags)
{
    if(flags & GAUSSIAN_FLAG)
    {
        cv::GaussianBlur(frame,frame,cv::Size(9,9),0);
    }
}

int process_image(int pattern, std::string file, int flags)
{
    cv::Mat test = cv::imread(file);

    cv::imshow("test", test);
    cv::waitKey(0);

    return 0;
}

//wrapper for all filters
void applyFilters(cv::Mat & frame, int flags)
{
            //checks sobel flag and applies the filter if so
            sobelOperator(frame,flags);
            //checks sharpen flag and applies the filter if so
            SharpeningFilter(frame,flags);
            //checks if Gaussian Flag enabled and applies if so
            GaussianBlur(frame,flags);
}