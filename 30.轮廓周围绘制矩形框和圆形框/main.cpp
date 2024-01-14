#include <opencv2/opencv.hpp>
#include <iostream>

cv::Mat src, gray_src, drawImg;
int threshold_v = 100;
int threshold_max = 255;
const char* output_win = "rectangle-demo";
cv::RNG rng(12345);
void Contours_CallBack(int, void*);

int main(int argc, char** argv){
    src = cv::imread("../../source/qiqiu.png");
    if(src.empty()){
        std::cout << "could not load image..." << std::endl;
        return -1;
    }
    cv::cvtColor(src, gray_src, cv::COLOR_BGR2GRAY);
    cv::blur(gray_src, gray_src, cv::Size(3, 3));

    const char* source_win = "input_image";
    cv::namedWindow(source_win);
    cv::namedWindow(output_win);
    cv::imshow(source_win, src);

    cv::createTrackbar("Threshold Value: ", output_win, &threshold_v, threshold_max, Contours_CallBack);
    Contours_CallBack(0, 0);

    cv::waitKey(0);
    return 0;
}

void Contours_CallBack(int, void*){
    cv::Mat binary_output;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierachy;
    cv::threshold(gray_src, binary_output, threshold_v, threshold_max, cv::THRESH_BINARY);
    cv::imshow("threshold", binary_output);
    cv::findContours(binary_output, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    std::vector<std::vector<cv::Point>> contours_ploy(contours.size());
    std::vector<cv::Rect> ploy_rects(contours.size());
    std::vector<cv::Point2f> ccs(contours.size());
    std::vector<float> radius(contours.size());

    std::vector<cv::RotatedRect> minRects(contours.size());
    std::vector<cv::RotatedRect> myellipse(contours.size());

    for(size_t i = 0; i < contours.size(); i++){
        cv::approxPolyDP(cv::Mat(contours[i]), contours_ploy[i], 3, true);
        ploy_rects[i] = cv::boundingRect(contours_ploy[i]);
        cv::minEnclosingCircle(contours_ploy[i], ccs[i], radius[i]);
        if(contours_ploy[i].size() > 5){
            myellipse[i] = cv::fitEllipse(contours_ploy[i]);
            minRects[i] = cv::minAreaRect(contours_ploy[i]);
        }

    }

    src.copyTo(drawImg);
    cv::Point2f pts[4];
    for(size_t t = 0; t < contours.size(); t++){
        cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        cv::rectangle(drawImg, ploy_rects[t], color, 2, 8);
        cv::circle(drawImg, ccs[t], radius[t], color, 2, 8);
        if(contours_ploy[t].size() > 5){
            cv::ellipse(drawImg, myellipse[t], color, 2, 8);
            minRects[t].points(pts);
            for(int r = 0; r < 4; r++){
                cv::line(drawImg, pts[r], pts[(r + 1) % 4], color, 2, 8);
            }
        }
    }
    cv::imshow(output_win, drawImg);
}