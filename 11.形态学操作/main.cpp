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

    cv::Mat src1 = cv::imread("../../source/binary.png");
    if(src1.empty()){
        std::cout << "could not load image..." << std::endl;
        return -1;
    }
    cv::namedWindow("src1 img");
    cv::imshow("src1 img", src1);

    cv::Mat src2 = cv::imread("../../source/binary1.png");
    if(src2.empty()){
        std::cout << "could not load image..." << std::endl;
        return -1;
    }
    cv::namedWindow("src2 img");
    cv::imshow("src2 img", src2);

    // MORPH_RECT = 0, MORPH_CROSS = 1, MORPH_ELLIPSE = 2 
    cv::Mat structureElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
    
    cv::Mat open_img;
    cv::morphologyEx(src1, open_img, cv::MORPH_OPEN, structureElement);
    cv::namedWindow("open img");
    cv::imshow("open img", open_img);

    cv::Mat top_hat_img;
    cv::morphologyEx(src1, top_hat_img, cv::MORPH_TOPHAT, structureElement);
    cv::namedWindow("top hat img");
    cv::imshow("top hat img", top_hat_img);

    /************************************************************************************/
    cv::Mat structureElement1 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(13, 13));

    cv::Mat close_img;
    cv::morphologyEx(src2, close_img, cv::MORPH_CLOSE, structureElement1);
    cv::namedWindow("close img");
    cv::imshow("close img", close_img);

    cv::Mat black_hat_img;
    cv::morphologyEx(src2, black_hat_img, cv::MORPH_BLACKHAT, structureElement1);
    cv::namedWindow("black hat img");
    cv::imshow("black hat img", black_hat_img);

    cv::Mat morp_img;
    cv::morphologyEx(src, morp_img, cv::MORPH_GRADIENT, structureElement);
    cv::namedWindow("morp img");
    cv::imshow("morp img", morp_img);
    cv::waitKey();

}