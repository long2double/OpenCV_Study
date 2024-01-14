#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){
    cv::Mat src = cv::imread("../../source/lena.png");
    if(src.empty()){
        std::cout << "could not load image..." << std::endl;
        return -1;
    }
    cv::namedWindow("src img", cv::WINDOW_AUTOSIZE);
    cv::imshow("src img", src);
    /**************************sobel算子************************/
    // x方向
    cv::Mat x_dst;
    cv::Sobel(src, x_dst, CV_64F, 1, 0, 3);
    cv::convertScaleAbs(x_dst, x_dst);
    cv::imshow("x_dst img", x_dst);

    // y方向
    cv::Mat y_dst;
    cv::Sobel(src, y_dst, CV_64F, 0, 1, 3);
    cv::convertScaleAbs(y_dst, y_dst);
    cv::imshow("y_dst img", y_dst);

    // x-y方向
    cv::Mat xy_dst;
    cv::Sobel(src, xy_dst, CV_64F, 1, 1, 3);
    cv::convertScaleAbs(xy_dst, xy_dst);
    cv::imshow("xy_dst img", xy_dst);

    /************************scharr算子**************************/
    // x方向
    cv::Mat x_scharr_dst;
    cv::Scharr(src, x_scharr_dst, CV_64F, 1, 0, 3);
    cv::convertScaleAbs(x_scharr_dst, x_scharr_dst);
    cv::imshow("x_scharr_dst img", x_scharr_dst);

    // y方向
    cv::Mat y_scharr_dst;
    cv::Scharr(src, y_scharr_dst, CV_64F, 0, 1, 3);
    cv::convertScaleAbs(y_scharr_dst, y_scharr_dst);
    cv::imshow("y_scharr_dst img", y_scharr_dst);

    // 不支持x-y方向
    // cv::Scharr(src, xy_scharr_dst, -1, 1, 1, 3);
    cv::waitKey();
}