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

    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, gray, cv::Size(3, 3), 11, 11);
    cv::Mat dst, edge;
    dst.create(src.size(), src.type());
    cv::Canny(gray, edge, 50, 150);
    cv::imshow("canny", edge);
    src.copyTo(dst, edge);
    cv::imshow("dst", dst);
    cv::waitKey();
}