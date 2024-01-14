#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){
    cv::Mat src = cv::imread("../../source/lena.png");
    if(src.empty()){
        std::cout << "could not load image ..." << std::endl;
        return -1;
    }

    cv::namedWindow("src img");
    cv::imshow("src img", src);

    cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);
    cv::Mat thre_img;
    cv::threshold(src, thre_img, 127, 255, cv::THRESH_BINARY);

    cv::namedWindow("thre img");
    cv::imshow("thre img", thre_img);
    cv::waitKey();
}