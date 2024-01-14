#include <opencv4/opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){
    cv::Mat src = cv::imread("/home/long2double/Desktop/OpenCV_Study/source/lena.png");
    if(src.empty()){
        std::cout << "could not load image ...." << std::endl;
        return -1;
    }
    cv::namedWindow("test opencv setup");
    cv::imshow("test opencv setup", src);
    cv::waitKey();
}