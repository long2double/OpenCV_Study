#include <opencv4/opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){
    cv::Mat src = cv::imread("/home/long2double/Desktop/OpenCV_Study/source/lena.png");
    if(src.empty()){
        std::cout << "could not load image ...." << std::endl;
        return -1;
    }
    cv::namedWindow("test opencv setup");
    cv::imshow("test opencv setup", src);

    // 拆分通道
    std::vector<cv::Mat> bgr_planes;
    cv::split(src, bgr_planes);

    // 计算直方图
    int histSize = 256;
    float range[] = {0, 256};
    const float *histRanges = {range};
    cv::Mat b_hist, g_hist, r_hist;
    cv::calcHist(&bgr_planes[0], 1, 0, cv::Mat(), b_hist, 1, &histSize, &histRanges, true, false);
    cv::calcHist(&bgr_planes[1], 1, 0, cv::Mat(), g_hist, 1, &histSize, &histRanges, true, false);
    cv::calcHist(&bgr_planes[2], 1, 0, cv::Mat(), r_hist, 1, &histSize, &histRanges, true, false);  
    
    // 归一化
    int hist_h = 400;
    int hist_w = 512;
    int bin_w = hist_w / histSize;
    cv::normalize(b_hist, b_hist, 0, hist_h, cv::NORM_MINMAX);
    cv::normalize(g_hist, g_hist, 0, hist_h, cv::NORM_MINMAX);
    cv::normalize(r_hist, r_hist, 0, hist_h, cv::NORM_MINMAX);

    // 计算直方图
    cv::Mat histImage(hist_w, hist_h, CV_8UC3, cv::Scalar(0, 0, 0));
    for(int i = 1; i < histSize; i++){
        cv::line(histImage, cv::Point((i - 1) * bin_w, hist_h - cvRound(b_hist.at<float>(i - 1))),
        cv::Point(i * bin_w, hist_h - cvRound(b_hist.at<float>(i))), cv::Scalar(255, 0, 0), 2, cv::LINE_AA);

        cv::line(histImage, cv::Point((i - 1) * bin_w, hist_h - cvRound(g_hist.at<float>(i - 1))),
        cv::Point(i * bin_w, hist_h - cvRound(g_hist.at<float>(i))), cv::Scalar(0, 255, 0), 2, cv::LINE_AA);

        cv::line(histImage, cv::Point((i - 1) * bin_w, hist_h - cvRound(r_hist.at<float>(i - 1))),
        cv::Point(i * bin_w, hist_h - cvRound(r_hist.at<float>(i))), cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
    }

    cv::imshow("histImage", histImage);
    cv::waitKey();
}