#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){
    cv::Mat src = cv::imread("../../source/line.png");
    if(src.empty()){
        std::cout << "could not load image ...." << std::endl;
        return -1;
    }
    cv::namedWindow("src img");
    cv::imshow("src img", src);

    // 转换为灰度图
    cv::Mat gray_img;
    cv::cvtColor(src, gray_img, cv::COLOR_BGR2GRAY);
    cv::namedWindow("gray img");
    cv::imshow("gray img", gray_img);
    // 反转，形态学操作针对前景，既白色；而现有图片白色为背景
    cv::bitwise_not(gray_img, gray_img);
    cv::namedWindow("bitwise not img");
    cv::imshow("bitwise not img", gray_img);
    // 自适应预置，转为二值图
    cv::Mat binary_img;
    cv::adaptiveThreshold(gray_img, binary_img, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 15, -3);
    cv::namedWindow("binary img");
    cv::imshow("binary img", binary_img);
    // 定义水平结构元素
    cv::Mat hlin = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(binary_img.cols / 8, 1));
    // 水平线
    cv::Mat h_img;
    cv::morphologyEx(binary_img, h_img, cv::MORPH_OPEN, hlin);
    cv::namedWindow("h img");
    cv::imshow("h img", h_img);
    // blur
    cv::blur(h_img, h_img, cv::Size(3, 3));
    cv::namedWindow("final h img");
    cv::imshow("final h img", ~h_img);  // 加反转

    // 定义垂直结构元素
    cv::Mat vlin = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(1, binary_img.rows / 8));
    // 垂直线
    cv::Mat v_img;
    cv::morphologyEx(binary_img, v_img, cv::MORPH_OPEN, vlin);
    cv::namedWindow("v img");
    cv::imshow("v img", v_img);
    // blur
    cv::blur(v_img, v_img, cv::Size(3, 3));
    cv::namedWindow("final v img");
    cv::imshow("final v img", ~v_img);  // 加反转

    cv::waitKey();
}