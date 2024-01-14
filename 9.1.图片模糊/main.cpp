#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** agrv){
    cv::Mat src = cv::imread("../../source/lena.png");
    if(src.empty()){
        std::cout << "could not load image..." << std::endl;
        return -1;
    }

    cv::namedWindow("src img");
    cv::imshow("src img", src);

    cv::Mat blur_img;
    cv::blur(src, blur_img, cv::Size(7, 7));
    cv::namedWindow("blur img");
    cv::imshow("blur img", blur_img);

    cv::Mat gau_img;
    cv::GaussianBlur(src, gau_img, cv::Size(7, 7), 11, 11);
    cv::namedWindow("gau img");
    cv::imshow("gau img", gau_img);
    cv::waitKey();

}