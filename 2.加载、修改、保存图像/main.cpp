#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){
    cv::Mat src = cv::imread("../../source/lena.png");
    if(src.empty()){
        std::cout << "could not load image ..." << std::endl;
        return -1;
    }

    cv::namedWindow("src img", cv::WINDOW_AUTOSIZE);
    cv::imshow("src img", src);

    cv::Mat out;
    cv::cvtColor(src, out, cv::COLOR_BGR2GRAY);
    cv::namedWindow("out img", cv::WINDOW_NORMAL);
    cv::imshow("out img", out);

    cv::imwrite("../../output/out.png", out);
    cv::waitKey();
}