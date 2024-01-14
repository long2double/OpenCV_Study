#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){
    cv::Mat src = cv::imread("../../source/lena.png");
    if(src.empty()){
        std::cout << "could not load image..." << std::endl;
        return -1;
    }

    cv::imshow("src", src);
    
    // top,bottom,left,right
    int top = 0.1 * src.rows;
    int bottom = 0.1 * src.rows;
    int left = 0.1 * src.cols;
    int right = 0.1 * src.cols;
    cv::Mat dst_constant, dst_replicate, dst_reflect, dst_wrap, dst_101;
    cv::copyMakeBorder(src, dst_constant, top, bottom, left, right, cv::BORDER_CONSTANT, cv::Scalar(255, 125, 125));
    cv::copyMakeBorder(src, dst_replicate, top, bottom, left, right, cv::BORDER_REPLICATE);
    cv::copyMakeBorder(src, dst_reflect, top, bottom, left, right, cv::BORDER_REFLECT);
    cv::copyMakeBorder(src, dst_wrap, top, bottom, left, right, cv::BORDER_WRAP);
    cv::copyMakeBorder(src, dst_101, top, bottom, left, right, cv::BORDER_REFLECT_101);

    cv::imshow("dst_constant", dst_constant);
    cv::imshow("dst_replicate", dst_replicate);
    cv::imshow("dst_reflect", dst_reflect);
    cv::imshow("dst_wrap", dst_wrap);
    cv::imshow("dst_101", dst_101);
    cv::waitKey();
}