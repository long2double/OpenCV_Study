#include <opencv2/opencv.hpp>
#include <iostream>
 
using namespace cv;
int main(int argc, char** argv){
    cv::Mat src = cv::imread("../../source/lena.png");
    if(src.empty()){
        std::cout << "could not load image ..." << std::endl;
        return -1;
    }
    cv::namedWindow("src img");
    cv::imshow("src img", src);

    cv::Mat dst1 = cv::Mat(src.size(), src.type());
    dst1 = cv::Scalar(127, 0, 255);
    cv::namedWindow("dst1");
    cv::imshow("dst1", dst1);

    cv::Mat dst2 = src.clone();  // 完全拷贝
    cv::namedWindow("dst2");
    cv::imshow("dst2", dst2);

    cv::Mat dst3;
    src.copyTo(dst3);  // 完全拷贝
    cv::namedWindow("dst3");
    cv::imshow("dst3", dst3);

    std::cout << "通道数:" << dst3.channels() << "宽: " << dst3.cols << "高: " << dst3.rows << std::endl; 
    cv::cvtColor(dst3, dst3, cv::COLOR_BGR2GRAY);
    std::cout << "通道数:" << dst3.channels() << "宽: " << dst3.cols << "高: " << dst3.rows << std::endl;

    cv::Mat M(100, 1100, CV_8UC3, cv::Scalar(127, 0, 255));
    cv::namedWindow("3_3");
    cv::imshow("3_3", M);

    cv::Mat dst4;
    dst4.create(src.size(), src.type());
    dst4 = cv::Scalar(127, 127, 255);
    cv::namedWindow("dst4");
    cv::imshow("dst4", dst4);

    //定义小的数组
    cv::Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cv::filter2D(src, dst4, src.depth(), kernel);
    cv::imshow("dst5", dst4);

    // cv::Mat::zeros(src.size(), src.type());
    // cv::Mat::zeros(10, 10, CV_8UC3);
    
    cv::waitKey();
}