#include <opencv2/opencv.hpp>
#include <iostream>

int threshold_value = 100;
int threshold_max = 255;
cv::RNG rng;
cv::Mat src, dst;

void Demo_Contours(int, void*);

int main(int argc, char** argv){
    src = cv::imread("../../source/happyfish.png");
    if(src.empty()){
        std::cout << "could not load image..." << std::endl;
        return -1;
    }
    cv::namedWindow("src");
    cv::namedWindow("output");
    cv::imshow("src", src);

    cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);
    const char* trackbar_title = "Threshold Value";
    cv::createTrackbar(trackbar_title, "output", &threshold_value, threshold_max, Demo_Contours);
    Demo_Contours(0, 0);

    cv::waitKey();
}


void Demo_Contours(int, void*){
    cv::Mat canny_out;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierachy;
    cv::Canny(src, canny_out, threshold_value, threshold_value * 2, 3, false);
    cv::findContours(canny_out, contours, hierachy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

    dst = cv::Mat::zeros(src.size(), CV_8UC3);
    rng(12345);
    for(int i = 0; i < contours.size(); i++){
        cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        cv::drawContours(dst, contours, i, color, 2, 8, hierachy, 0);
    }
    cv::imshow("output", dst);
}
