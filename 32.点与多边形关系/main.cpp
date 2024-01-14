#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){
    const int r = 100;
    cv::Mat src = cv::Mat::zeros(r * 4, r * 4, CV_8UC1);

    std::vector<cv::Point2f> vert(6);
    vert[0] = cv::Point(3 * r / 2, static_cast<int>(1.34 * r));
    vert[1] = cv::Point(1 * r, 2 * r);
    vert[2] = cv::Point(3 * r / 2, static_cast<int>(2.866 * r));
    vert[3] = cv::Point(5 * r / 2, static_cast<int>(2.866 * r));
    vert[4] = cv::Point(3 * r, 2 * r);
    vert[5] = cv::Point(5 * r / 2, static_cast<int>(1.34 * r));

    for(int i = 0; i < 6; i++){
        cv::line(src, vert[i], vert[(i + 1) % 6], cv::Scalar(255), 3, 8, 0);
    }

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierachy;
    cv::Mat csrc;
    src.copyTo(csrc);
    cv::findContours(csrc, contours, hierachy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    cv::Mat raw_dist = cv::Mat::zeros(csrc.size(), CV_32FC1);
    for(int row = 0; row < raw_dist.rows; row++){
        for(int col = 0; col < raw_dist.cols; col++){
            double dist = cv::pointPolygonTest(contours[0], cv::Point2f(static_cast<float>(col), static_cast<float>(row)), true);
            raw_dist.at<float>(row, col) = static_cast<float>(dist);
        }
    }

    double minValue, maxValue;
    cv::minMaxLoc(raw_dist, &minValue, &maxValue, 0, 0);
    cv::Mat drawImg = cv::Mat::zeros(src.size(), CV_8UC3);
    for(int row = 0; row < drawImg.rows; row++){
        for(int col = 0; col < drawImg.cols; col++){
            double dist = raw_dist.at<float>(row, col);
            if(dist > 0){
                drawImg.at<cv::Vec3b>(row, col)[0] = (uchar)(abs(1.0 - dist / maxValue) * 255);
            }
            else if(dist < 0){
                drawImg.at<cv::Vec3b>(row, col)[2] = (uchar)(abs(1.0 - dist / minValue) * 255);
            }
            else{
                drawImg.at<cv::Vec3b>(row, col)[0] = (uchar)(abs(255 - dist));
                drawImg.at<cv::Vec3b>(row, col)[1] = (uchar)(abs(255 - dist));
                drawImg.at<cv::Vec3b>(row, col)[2] = (uchar)(abs(255 - dist));
            }
        }
    }

    const char* output_win = "point polygon test demo";
    char input_win[] = "input image";
    cv::namedWindow(input_win, cv::WINDOW_AUTOSIZE);
    cv::namedWindow(output_win, cv::WINDOW_AUTOSIZE);

    cv::imshow(input_win, src);
    cv::imshow(output_win, drawImg);
    cv::waitKey();

    return -1;
}