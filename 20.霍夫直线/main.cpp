#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){
    cv::Mat src = cv::imread("../../source/line1.png");
    if(src.empty()){
        std::cout << "could not load image..." << std::endl;
        return -1;
    }
    cv::namedWindow("src img", cv::WINDOW_AUTOSIZE);
    cv::imshow("src img", src);

    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    cv::Mat edge;
    cv::Canny(gray, edge, 100, 200);
    cv::imshow("edge", edge);

    std::vector<cv::Vec4f> vec_lines;
    cv::HoughLinesP(edge, vec_lines, 1, CV_PI / 180.0, 10, 0, 10);
    for(int i = 0; i < vec_lines.size(); i++){
        cv::Vec4f hline = vec_lines[i];
        cv::line(src, cv::Point(hline[0], hline[1]), cv::Point(hline[2], hline[3]), cv::Scalar(0, 255, 255), 2, cv::LINE_AA);
    }
    cv::imshow("result", src);
    cv::waitKey();
}