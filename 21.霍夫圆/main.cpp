#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){
    cv::Mat src = cv::imread("../../source/circle.png");
    if(src.empty()){
        std::cout << "could not load image..." << std::endl;
        return -1;
    }
    cv::namedWindow("src img", cv::WINDOW_AUTOSIZE);
    cv::imshow("src img", src);

    cv::medianBlur(src, src, 3);
    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    std::vector<cv::Vec3f> vec_circle;
    cv::HoughCircles(gray, vec_circle, cv::HOUGH_GRADIENT, 1, 10, 100, 30, 5, 50);
    for(int i = 0; i < vec_circle.size(); i++){
        cv::Vec3f cc = vec_circle[i];
        cv::circle(src, cv::Point(cc[0], cc[1]), cc[2], cv::Scalar(0, 255, 255), 2, cv::LINE_AA);
        cv::circle(src, cv::Point(cc[0], cc[1]), 2, cv::Scalar(128, 128, 255), 2, cv::LINE_AA);
    }
    cv::imshow("result", src);
    cv::waitKey();
}