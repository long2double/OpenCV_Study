#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){
    cv::Mat src = cv::imread("../../source/lena.png");
    if(src.empty()){
        std::cout << "could not load image..." << std::endl;
        return -1;
    }

    cv::imshow("src", src);
    // blur
    int size = 2 * 3 + 1;
    cv::Mat kernel = cv::Mat::ones(cv::Size(size, size), CV_32F) / static_cast<float>(size * size);
    cv::Mat dst_blur;
    cv::filter2D(src, dst_blur, -1, kernel);
    cv::imshow("dst_blur", dst_blur);

    // roberrt +45方向
    cv::Mat dst_roberrt_x;
    cv::Mat kernel_1 = (cv::Mat_<int>(2, 2) << 1, 0, 0, -1);
    cv::filter2D(src, dst_roberrt_x, -1, kernel_1);
    cv::imshow("dst_roberrt_x", dst_roberrt_x);
    // roberrt -45方向
    cv::Mat dst_roberrt_y;
    cv::Mat kernel_2 = (cv::Mat_<int>(2, 2) << 0, 1, -1, 0);
    cv::filter2D(src, dst_roberrt_y, -1, kernel_2);
    cv::imshow("dst_roberrt_y", dst_roberrt_y);

    // sobel x方向
    cv::Mat dst_sobel_x;
    cv::Mat kernel_3 = (cv::Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
    cv::filter2D(src, dst_sobel_x, -1, kernel_3);
    cv::imshow("dst_sobel_x", dst_sobel_x);
    // sobel y方向
    cv::Mat dst_sobel_y;
    cv::Mat kernel_4 = (cv::Mat_<int>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
    cv::filter2D(src, dst_sobel_y, -1, kernel_4);
    cv::imshow("dst_sobel_y", dst_sobel_y);

    // 拉普拉斯
    cv::Mat dst_lapl;
    cv::Mat kernel_5 = (cv::Mat_<int>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
    cv::filter2D(src, dst_lapl, -1, kernel_5);
    cv::imshow("dst_lapl", dst_lapl);
    cv::waitKey();
}