#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

cv::Mat src, dst;
int threshold_value = 127;
int threshold_max = 255;
const char* input_win = "input image";
const char* output_win = "output image";
cv::RNG rng(1234);

void Threshold_CallBack(int, void*);


int main(int argc, char** argv){
    src = cv::imread("../../source/convexhull.png");
    if(src.empty()){
        std::cout << "could not load image..." << std::endl;
        return -1;
    }

    cv::namedWindow(input_win, cv::WINDOW_AUTOSIZE);
    cv::namedWindow(output_win, cv::WINDOW_AUTOSIZE);
    cv::imshow(input_win, src);

    const char* trackbar_label = "Threshold: ";

    cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);
    cv::blur(src, src, cv::Size(3, 3), cv::Point(-1, -1));

    cv::createTrackbar(trackbar_label, output_win, &threshold_value, threshold_max, Threshold_CallBack);
    Threshold_CallBack(0, 0);
    cv::waitKey(0);
    return 0;
}


void Threshold_CallBack(int, void*){
    cv::Mat bin_output;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierachy;
    cv::threshold(src, bin_output, threshold_value, threshold_max, cv::THRESH_BINARY);

    cv::findContours(bin_output, contours, hierachy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    std::vector<std::vector<cv::Point>> convexs(contours.size());
    for(size_t i = 0; i < contours.size(); i++){
        cv::convexHull(contours[i], convexs[i], false, true);
    }
    
    dst = cv::Mat::zeros(src.size(), CV_8UC3);
    std::vector<cv::Vec4i> empty(0);
    for(size_t k = 0; k < contours.size(); k++){
        cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        cv::drawContours(dst, contours, k, color, 2, cv::LINE_8, hierachy);
        cv::drawContours(dst, convexs, k, color, 2, cv::LINE_8, empty);
    }
    cv::imshow(output_win, dst);
}
