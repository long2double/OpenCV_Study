#include <opencv2/opencv.hpp>
#include <iostream>

cv::Mat src, temp, dst;
int match_method = cv::TM_SQDIFF;
int max_track = 5;
const char* INPUT_T = "input image";
const char* OUTPUT_T = "result image";
const char* match_t = "template match-demo";
void Match_Demo(int, void*);


int main(int argc, char** argv){
    // 待检测图片
    src = cv::imread("../../source/dog.png");
    // 模板
    temp = cv::imread("../../source/dog_tmp.png");
    if(src.empty() || temp.empty()){
        std::cout << "could not load image..." << std::endl;
        return -1;
    }
    cv::namedWindow(INPUT_T, cv::WINDOW_AUTOSIZE);
    cv::namedWindow(OUTPUT_T, cv::WINDOW_AUTOSIZE);
    cv::namedWindow(match_t, cv::WINDOW_AUTOSIZE);

    cv::imshow(INPUT_T, temp);

    const char* trackbar_title = "Match Algo Type";
    cv::createTrackbar(trackbar_title, OUTPUT_T, &match_method, max_track, Match_Demo);
    Match_Demo(0, 0);
    cv::waitKey(0);
}

void Match_Demo(int, void*){
    int width = src.cols - temp.cols + 1;
    int height = src.rows - temp.rows + 1;
    cv::Mat result(width, height, CV_32FC1);
    cv::matchTemplate(src, temp, result, match_method, cv::Mat());
    cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

    cv::Point minLoc;
    cv::Point maxLoc;
    double min, max;
    src.copyTo(dst);
    cv::Point temLoc;
    cv::minMaxLoc(result, &min, &max, &minLoc, &maxLoc, cv::Mat());
    if(match_method == cv::TM_SQDIFF || match_method == cv::TM_SQDIFF_NORMED){
        temLoc = minLoc;
    }
    else{
        temLoc = maxLoc;
    }
    cv::rectangle(dst, cv::Rect(temLoc.x, temLoc.y, temp.cols, temp.rows), cv::Scalar(0, 0, 255), 2);
    cv::rectangle(result, cv::Rect(temLoc.x, temLoc.y, temp.cols, temp.rows), cv::Scalar(0, 0, 255), 2);
    imshow(OUTPUT_T, result);
    imshow(match_t, dst);
}