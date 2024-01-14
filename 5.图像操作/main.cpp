#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){
    cv::Mat src = cv::imread("../../source/lena.png");
    if(src.empty()){
        std::cout << "could not load image ..." << std::endl;
        return -1;
    }
    cv::namedWindow("src img");
    cv::imshow("src img", src);

    cv::Mat gray_img;
    cv::cvtColor(src, gray_img, cv::COLOR_BGR2GRAY);
    // int channels = gray_img.channels();

    cv::Mat dst;
    dst.create(src.size(), src.type());
    int cols = dst.cols;
    int rows = dst.rows;
    int channels = dst.channels();
    for(int i = 0; i < rows; i++){// 
        for(int j = 0; j < cols; j++){
            // 单通道 
            if(channels == 1){
                int pixel = gray_img.at<uchar>(i, j);
                gray_img.at<uchar>(i, j) = 255 - pixel;
            } 
            else if(channels == 3){
                int b = src.at<cv::Vec3b>(i, j)[0];
                int g = src.at<cv::Vec3b>(i, j)[1];
                int r = src.at<cv::Vec3b>(i, j)[2];
                dst.at<cv::Vec3b>(i, j)[0] = 255 - b;
                dst.at<cv::Vec3b>(i, j)[1] = 255 - g;
                dst.at<cv::Vec3b>(i, j)[2] = 255 - b;
            }
        }
    }

    // 类型转换，但CV_16FC3不支持显示
    // src.convertTo(dst, CV_16FC3);

    // cv::bitwise_not(src, dst);
    
    cv::namedWindow("dst img");
    cv::imshow("dst img", dst); 

    cv::waitKey();
}