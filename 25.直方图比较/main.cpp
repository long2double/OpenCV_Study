#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

std::string convertToString(double d);


int main(int argc, char** argv){
    cv::Mat src1 = cv::imread("../../source/lena.png");
    cv::Mat src2 = cv::imread("../../source/matlab.jpeg");
    if(src1.empty() && src2.empty()){
        std::cout << "could not load image ...." << std::endl;
        return -1;
    }

    cv::cvtColor(src1, src1, cv::COLOR_BGR2HSV);
    cv::cvtColor(src2, src2, cv::COLOR_BGR2HSV);

    int h_bins = 50;
    int s_bins = 60;
    int histSize[] = {h_bins, s_bins};
    // hue varies from 0 to 179, saturation from 0 to 255
    float h_ranges[] = {0, 180};
    float s_ranges[] = {0, 256};
    const float* ranges[] = {h_ranges, s_ranges};
    // Use the o-th and 1-st channels
    int channels[] = {0, 1};
    cv::MatND hist_src1, hist_src2;

    cv::calcHist(&src1, 1, channels, cv::Mat(), hist_src1, 2, histSize, ranges, true, false);
    cv::normalize(hist_src1, hist_src1, 0, 1, cv::NORM_MINMAX);
    cv::calcHist(&src2, 1, channels, cv::Mat(), hist_src2, 2, histSize, ranges, true, false);
    cv::normalize(hist_src2, hist_src2, 0, 1, cv::NORM_MINMAX);

    double base = cv::compareHist(hist_src1, hist_src1, cv::HISTCMP_CORREL);
    double base1 = cv::compareHist(hist_src1, hist_src2, cv::HISTCMP_CORREL);

    cv::putText(src1, convertToString(base), cv::Point(30, 30), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 255, 255));
    cv::putText(src2, convertToString(base1), cv::Point(30, 30), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 255, 255));

    cv::imshow("src1", src1);
    cv::imshow("src2", src2);
    cv::waitKey();
}


std::string convertToString(double d){
    std::ostringstream os;
    if(os << d){
        return os.str();
    }
    return "invalid conversion";
}
