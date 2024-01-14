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
    
    cv::Mat down_img, up_img;
    cv::pyrDown(src, down_img);
    cv::pyrUp(src, up_img);

    cv::namedWindow("Down img");
    cv::namedWindow("Up img");
    cv::imshow("Down img", down_img);
    cv::imshow("Up img", up_img);

    cv::Mat dog1, dog2, dog_img;
    cv::GaussianBlur(src, dog1, cv::Size(5, 5), 11);
    cv::GaussianBlur(dog1, dog2, cv::Size(5, 5), 11);
    cv::subtract(dog1, dog2, dog_img);
    cv::namedWindow("dog img");
    cv::normalize(dog_img, dog_img, 255, 0, cv::NORM_MINMAX);
    cv::imshow("dog img", dog_img);

    cv::waitKey();
}