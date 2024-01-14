#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){
    cv::Mat src = cv::imread("../../source/lena.png");
    if(src.empty()){
        std::cout << "could not load image..." << std::endl;
        return -1;
    }

    // cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);
    cv::namedWindow("src");
    cv::imshow("src", src);

    int alpha = 2;
    int beta = 40;
    int rows = src.rows;
    int cols = src.cols;
    cv::Mat dst = cv::Mat::zeros(src.size(), src.type());
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(src.channels() == 3){
                float b = src.at<cv::Vec3b>(i, j)[0];
                float g = src.at<cv::Vec3b>(i, j)[1];
                float r = src.at<cv::Vec3b>(i, j)[2];

                dst.at<cv::Vec3b>(i, j)[0] = cv::saturate_cast<uchar>(alpha * b + beta);
                dst.at<cv::Vec3b>(i, j)[1] = cv::saturate_cast<uchar>(alpha * g + beta);
                dst.at<cv::Vec3b>(i, j)[2] = cv::saturate_cast<uchar>(alpha * r + beta);
            }else{
                dst.at<uchar>(i, j) = cv::saturate_cast<uchar>(alpha * src.at<uchar>(i, j) + beta);
            }
        }
    }

    cv::namedWindow("contract and brightness");
    cv::imshow("contract and brightness", dst);
    cv::waitKey();
}