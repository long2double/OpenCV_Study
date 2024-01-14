#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){
    cv::RNG rng;
    cv::Point p1, p2;
    cv::Mat plot = cv::Mat::zeros(cv::Size(800, 800), CV_8UC3);
    for(int i = 1; i < 10000; i++){
        p1.x = rng.uniform(0, plot.rows);
        p1.y = rng.uniform(0, plot.cols);
        p2.x = rng.uniform(0, plot.rows);
        p2.y = rng.uniform(0, plot.cols);

        cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        cv::line(plot, p1, p2, color, 2, cv::LINE_AA);
        cv::namedWindow("random plot line");
        cv::imshow("random plot line", plot);

        if(i < 400){
            cv::waitKey(10);
        }else{
            cv::waitKey();
            break;
        }
    }
}