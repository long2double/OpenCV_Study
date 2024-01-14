#include <opencv2/opencv.hpp>
#include <iostream>

void MyLine(cv::Mat &tmp);
void MyRectangle(cv::Mat &tmp);
void MyCircle(cv::Mat &tmp);
void MyEllipse(cv::Mat &tmp);

int main(int argc, char** argv){
    cv::Mat src = cv::imread("../../source/lena.png");
    if(src.empty()){
        std::cout << "could not load image ..." << std::endl;
        return -1;
    }

    MyLine(src);
    MyRectangle(src);
    MyCircle(src);
    MyEllipse(src);
    cv::putText(src, "Hello Opencv", cv::Point(256, 45), cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 1.0, cv::Scalar(125, 215, 255));

    cv::namedWindow("draw picture");
    cv::imshow("draw picture", src);
    cv::waitKey();
}

void MyLine(cv::Mat &tmp){
    cv::Point p1 = cv::Point(10, 10);
    cv::Point p2;
    p2.x = 100;
    p2.y = 100;
    cv::Scalar color = cv::Scalar(0, 0, 255);
    cv::line(tmp, p1, p2, color, 2, cv::LINE_AA);
}

void MyRectangle(cv::Mat &tmp){
    cv::Scalar color = cv::Scalar(0, 255, 0);
    cv::Rect rect = cv::Rect(45, 56, tmp.cols / 2, tmp.rows / 2);
    cv::rectangle(tmp, rect, color, 2, cv::LINE_AA);
}

void MyCircle(cv::Mat &tmp){
    cv::Scalar color = cv::Scalar(255, 0, 0);
    cv::Point c = cv::Point(tmp.cols / 2, tmp.rows / 2);
    cv::circle(tmp, c, 80, color, 2, cv::LINE_AA);
}

void MyEllipse(cv::Mat &tmp){
    cv::Scalar color = cv::Scalar(255, 0, 255);
    cv::ellipse(tmp, cv::Point(124, 345), cv::Size(50, 90), 90, 0, 360, color, 2, cv::LINE_AA);
}