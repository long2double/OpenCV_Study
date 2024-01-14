#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){
    cv::Mat src = cv::imread("../../source/lena.png");
    if(src.empty()){
        std::cout << "could not load image..." << std::endl;
        return -1;
    }
    cv::namedWindow("src img", cv::WINDOW_AUTOSIZE);
    cv::imshow("src img", src);

    cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);
    cv::blur(src, src, cv::Size(3, 3));
    cv::Mat dst;
    cv::Laplacian(src, dst, CV_16S, 3);
    cv::convertScaleAbs(dst, dst);
    cv::imshow("dst", dst);
    cv::waitKey();
}