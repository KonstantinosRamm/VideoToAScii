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
            frame_ascii += static_cast<char>(pixelValue);  // Convert to character
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


void ColorFilter(const cv::Mat &frame, int flags, std::string &ascii_frame)
{
    if (flags & COLOR_FLAG)
    {
        std::vector<std::string> color_vector;
        std::string current_ansi;
        std::string colored_ascii;
        unsigned int red = 0, green = 0, blue = 0;
        int width = frame.cols;
        int height = frame.rows;

        // Iterate through each pixel in the frame
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cv::Vec3b pixel = frame.at<cv::Vec3b>(i, j);
                blue = pixel[0];
                green = pixel[1];
                red = pixel[2];

                // Build the ANSI escape code for the current pixel's color
                current_ansi = "\033[38;2;" + std::to_string(red) + ";" + std::to_string(green) + ";" + std::to_string(blue) + "m";

                // Push color code to the vector
                color_vector.push_back(current_ansi);
            }

            // Add the RESET color code at the end of the line (if necessary)
            color_vector.push_back("\033[0m");  // Reset color after each line
        }

        // Now print the color codes with the ASCII frame characters
        for (int i = 0; i < color_vector.size(); i++) {
              // Print color and corresponding ASCII character
              colored_ascii += color_vector.at(i) + ascii_frame[i];
        }

        //restore the colored string in ascii_frame
        ascii_frame = colored_ascii;

    }
}



int process_image(int pattern, std::string file, int flags)
{
    std::vector<std::string> color_vector;
    cv::Mat image = cv::imread(file);
    if(image.empty())
    {
        std::cerr << "[ERROR] ivalid image" << std::endl;
        return -1;
    }

    //store terminal window dimensions
    struct winsize window_size;
    int width = 0;
    int height = 0;
    cv::Mat frame,grayScale,resized_mat;


    frame = image.clone();

    /*
        Intentionaly made a loop so the program runs and changes the 
        ascii art size dynamically based on size of terminal dimensions
    */
    while(true)
    {
        //read current dimensions of window
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size);

        //check if resize needed
        if (window_size.ws_row != height || window_size.ws_col != width)
        {
            std::string frame_ascii;
            height = window_size.ws_row;
            width = window_size.ws_col;          

            //convert to grayScale and resize
            cv::cvtColor(frame,grayScale,cv::COLOR_BGR2GRAY);
            cv::resize(grayScale,resized_mat, cv::Size(width,height),0,0,cv::INTER_CUBIC);
            
            applyFilters(resized_mat,flags);
            frame_ascii = convertToAscii(resized_mat,pattern);
            //apply color filter if activated  
            //the resize occurs just in case we use Color Filter since not resizing the frame will cause a distorted image
            cv::resize(frame,frame, cv::Size(width,height),0,0,cv::INTER_CUBIC);           
            ColorFilter(frame,flags,frame_ascii);
            std::cout << RESET_CURSOR;
            std::cout << frame_ascii;

        }
        

        //1 second delay between each iteration
        
        std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME));


    }

    
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
            //checks if Gaussian Flag enabled and applies if so
            GaussianBlur(frame,flags);
}
