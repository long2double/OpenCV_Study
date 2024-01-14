#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){
    cv::Mat src1 = cv::imread("../../source/lena.png");
    cv::Mat src2 = cv::imread("../../source/matlab.jpeg");
    if(src1.empty() or src2.empty()){
        std::cout << "could not load image ... " << std::endl;
        return -1;
    }

    cv::namedWindow("src1");
    cv::namedWindow("src2");
    cv::imshow("src1", src1);
    cv::imshow("src2", src2);

    cv::Mat dst(src1.size(), src1.type());
    if(src1.size() == src2.size() && src1.type() == src2.type()){
        cv::addWeighted(src1, 0.5, src2, 0.5, 0.0, dst);
    }
    else{
        std::cout << "target file not equal" << std::endl;
    }

    cv::namedWindow("dst");
    cv::imshow("dst", dst);
    cv::waitKey();
}