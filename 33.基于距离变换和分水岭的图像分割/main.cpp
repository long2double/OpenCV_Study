#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){
    char intput_win[] = "input image";
    cv::Mat src = cv::imread("../../source/segmetation_1.png");
    if(src.empty()){
        std::cout << "could not load image..." << std::endl;
        return -1;
    }

    cv::namedWindow(intput_win);
    cv::imshow(intput_win, src);
    
    for(int row = 0; row < src.rows; row++){
        for(int col = 0; col < src.cols; col++){
            if(src.at<cv::Vec3b>(row, col) == cv::Vec3b(255, 255, 255)){
                src.at<cv::Vec3b>(row, col)[0] = 0;
                src.at<cv::Vec3b>(row, col)[1] = 0;
                src.at<cv::Vec3b>(row, col)[2] = 0;
            }
        }
    }
    cv::namedWindow("black background");
    cv::imshow("black background", src);

    // sharpen
    cv::Mat kernel = (cv::Mat_<float>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
    cv::Mat imgLaplance;
    cv::filter2D(src, imgLaplance, CV_32F, kernel);
    cv::Mat sharpenImg;
    src.convertTo(sharpenImg, CV_32F);
    cv::Mat resultImg = sharpenImg - imgLaplance;

    // imgLaplance.convertTo(imgLaplance, CV_8UC3);
    // cv::imshow("imgLaplance image", imgLaplance);
    resultImg.convertTo(resultImg, CV_8UC3);
    // cv::imshow("sharpen image", resultImg);

    src = resultImg;

    // convert to binary
    cv::Mat binaryImg;
    cv::cvtColor(src, resultImg, cv::COLOR_BGR2GRAY);
    cv::threshold(resultImg, binaryImg, 127, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::imshow("binary image", binaryImg);

    cv::Mat distImg;
    cv::distanceTransform(binaryImg, distImg, cv::DIST_L2, 3, 5);
    cv::normalize(distImg, distImg, 0, 1, cv::NORM_MINMAX);
    cv::imshow("distance result", distImg);

    // binary again
    cv::threshold(distImg, distImg, 0.5, 1, cv::THRESH_BINARY);
    cv::imshow("distance binary result", distImg);

    cv::Mat k1 = cv::Mat::ones(3, 3, CV_8UC1);
    cv:erode(distImg, distImg, k1);
    cv::imshow("erode image", distImg);

    // markers
    cv::Mat dist_8u;
    distImg.convertTo(dist_8u, CV_8U);
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(dist_8u, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    
    cv::Mat markers = cv::Mat::zeros(src.size(), CV_32SC1);
    for(size_t i = 0; i < contours.size(); i++){
        cv::drawContours(markers, contours, static_cast<int>(i), cv::Scalar::all(static_cast<int>(i) + 1), -1);
    }
    // markers.convertTo(markers, CV_8UC3);
    // cv::circle(markers, cv::Point(5, 5), 3, cv::Scalar(255, 255, 255), -1);
    // cv::imshow("my markers", markers * 1000);

    // perform watershed
    // markers.convertTo(markers, CV_32SC1);
    cv::watershed(src, markers);
    cv::Mat mark = cv::Mat::zeros(markers.size(), CV_8UC1);
    markers.convertTo(mark, CV_8UC1);
    cv::bitwise_not(mark, mark);
    cv::imshow("watershed image", mark);

    // generate random color
    std::vector<cv::Vec3b> colors;
    for(size_t i = 0; i < contours.size(); i++){
        int r = cv::theRNG().uniform(0, 255);
        int g = cv::theRNG().uniform(0, 255);
        int b = cv::theRNG().uniform(0, 255);
        colors.push_back(cv::Vec3b((uchar)b, (uchar)g, (uchar)r));
    }

    // fill with color and display final result
    cv::Mat dst = cv::Mat::zeros(markers.size(), CV_8UC3);
    for(int row = 0; row < markers.rows; row++){
        for(int col = 0; col < markers.cols; col++){
            int index = markers.at<int>(row, col);
            if(index > 0 && index <= static_cast<int>(contours.size())){
                dst.at<cv::Vec3b>(row, col) = colors[index - 1];
            }
            else{
                dst.at<cv::Vec3b>(row, col) = cv::Vec3b(0, 0, 0);
            }
        }
    }

    imshow("Final Result", dst);
    cv::waitKey();
}