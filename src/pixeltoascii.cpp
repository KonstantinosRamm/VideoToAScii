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



int process_video(int pattern,std::string file,int flags)
{
    //read video from file 
    cv::VideoCapture video(file);
    if(!video.isOpened())
    {
        std::cerr << "[ERROR] opening video\n";
        std::cerr << "Falling back to default video\n";
        //recheck if default video opened 
         if(! video.open("sample/sample.mp4"))
        {
            std::cerr << "[ERROR] could not locate default video" << std::endl;
            return -1;
        }
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
        auto start_time = std::chrono::high_resolution_clock::now();
        //read current dimentions in order to resize accordingly
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        if (size.ws_row != height || size.ws_col != width)
        {
            height = size.ws_row;
            width = size.ws_col;
            //clear screen  to avoid messing up character printing 
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
        
        applyFilters(resized_mat,flags);

        //convert current frame to ascii
        frame_ascii = convertToAscii(resized_mat,pattern);

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








//wrapper for all filters
void applyFilters(cv::Mat & frame, int flags)
{
            //checks sobel flag and applies the filter if so
            sobelOperator(frame,flags);
            //checks sharpen flag and applies the filter if so
            SharpeningFilter(frame,flags);
}