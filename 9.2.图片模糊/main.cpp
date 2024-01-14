#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** agrv){
    cv::Mat src = cv::imread("../../source/lena.png");
    if(src.empty()){
        std::cout << "could not load image..." << std::endl;
        return -1;
    }

    cv::namedWindow("src img");
    cv::imshow("src img", src);

    cv::Mat blur_img;
    cv::blur(src, blur_img, cv::Size(3, 3));
    cv::namedWindow("blur img");
    cv::imshow("blur img", blur_img);

    cv::Mat gau_img;
    cv::GaussianBlur(src, gau_img, cv::Size(3, 3), 3);
    cv::namedWindow("gau img");
    cv::imshow("gau img", gau_img);

    cv::Mat median_img;
    cv::medianBlur(src, median_img, 3);
    cv::namedWindow("median img");
    cv::imshow("median img", median_img);

    cv::Mat bilateral_img;
    cv::bilateralFilter(src, bilateral_img, 15, 100, 3);
    cv::namedWindow("bilateral img");
    cv::imshow("bilateral img", bilateral_img);

    cv::Mat filter_img;
    cv::Mat kernel = (cv::Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cv::filter2D(bilateral_img, filter_img, -1, kernel);
    cv::namedWindow("filter img");
    cv::imshow("filter img", filter_img);
    cv::waitKey();

}