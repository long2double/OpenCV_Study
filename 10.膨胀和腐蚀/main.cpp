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

    // MORPH_RECT = 0, MORPH_CROSS = 1, MORPH_ELLIPSE = 2 
    cv::Mat structureElement = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(7, 7));
    
    cv::Mat dilate_img;
    cv::dilate(src, dilate_img, structureElement);
    cv::namedWindow("dilate img");
    cv::imshow("dilate img", dilate_img);
    
    cv::Mat erode_img;
    cv::erode(src, erode_img, structureElement);
    cv::namedWindow("erode img");
    cv::imshow("erode img", erode_img);

    cv::waitKey();

}