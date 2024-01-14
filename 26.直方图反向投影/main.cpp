#include <opencv2/opencv.hpp>
#include <iostream>

cv::Mat src, hsv, hue;
int bins = 12;
void Hist_And_Backproject(int, void*);

int main(int argc, char** argv){
    src = cv::imread("../../source/project.png");
    if(src.empty()){
        std::cout << "could not load image...\n" << std::endl;
        return -1;
    }

    const char* window_image = "input image";
    cv::namedWindow(window_image, cv::WINDOW_AUTOSIZE);
    cv::namedWindow("BackProj", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Histogram", cv::WINDOW_AUTOSIZE);

    cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
    hue.create(hsv.size(), hsv.depth());
    int nchannels[] = {0, 0};
    cv::mixChannels(&hsv, 1, &hue, 1, nchannels, 1);

    cv::createTrackbar("Histogram Bins: ", window_image, &bins, 180, Hist_And_Backproject);
    Hist_And_Backproject(0, 0);

    cv::imshow(window_image, src);
    cv::waitKey(0);
}

void Hist_And_Backproject(int, void*){
    float range[] = {0, 180};
    const float *histRanges = { range };
    cv::Mat h_hist;
    cv::calcHist(&hue, 1, 0, cv::Mat(), h_hist, 1, &bins, &histRanges, true, false);
    cv::normalize(h_hist, h_hist, 0, 255, cv::NORM_MINMAX, -1, cv::Mat());

    cv::Mat backProImage;
    cv::calcBackProject(&hue, 1, 0, h_hist, backProImage, &histRanges, 1, true);
    cv::imshow("BackProj", backProImage);

    int hist_h = 400;
    int hist_w = 512;
    cv::Mat histImage(hist_w, hist_h, CV_8UC3, cv::Scalar(0, 0, 0));
    int bin_w = hist_w / bins;
    for(int i = 1; i < bins; i++){
        cv::rectangle(histImage, cv::Point((i - 1) * bin_w, (hist_h - cvRound(h_hist.at<float>(i - 1) * (400 / 255)))),
        cv::Point(i * bin_w, hist_h),
        cv::Scalar(0, 0, 255), -1);
    }
    cv::imshow("Histogram", histImage);
}