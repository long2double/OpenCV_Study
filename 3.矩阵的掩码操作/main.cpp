#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){
    cv::Mat src = cv::imread("../../source/lena.png");
    if(src.empty()){
        std::cout << "could not load image..." << std::endl;
        return -1;
    }

    cv::namedWindow("src image", cv::WINDOW_AUTOSIZE);
    cv::imshow("src image", src);

    // 输出图片的宽、高和通道数
    std::cout << "图片的宽: " << src.cols << ", 高: " << src.rows << ", 通道数: " << src.channels() << std::endl;
    // 对原始图片进行掩码操作
    int channel = src.channels();
    int cols = (src.cols - 1) * channel;
    int rows = src.rows;
    
    cv::Mat dst = cv::Mat::zeros(src.size(), src.type());

    // 开始执行时间戳
    double t1 = cv::getTickCount();
    // for(int row_start = 1; row_start < rows; row_start++){
    //     const uchar* pre = src.ptr<uchar>(row_start - 1);
    //     const uchar* cur = src.ptr<uchar>(row_start);
    //     const uchar* next = src.ptr<uchar>(row_start + 1);

    //     uchar *dst_ptr = dst.ptr<uchar>(row_start);
    //     for(int col_start = 1; col_start < cols; col_start++){
    //         dst_ptr[col_start] = cv::saturate_cast<uchar>(5 * cur[col_start] - pre[col_start] - next[col_start] - cur[col_start - channel] - cur[col_start + channel]);
    //     }
    // }
    // 结束时间戳
    double t2 = cv::getTickCount();
    // opencv api执行操作
    std::cout << "执行所需要的时间: " << (t2 - t1) / cv::getTickFrequency() << std::endl;
    cv::Mat kernel = (cv::Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cv::filter2D(src, dst, src.depth(), kernel);

    cv::namedWindow("dst image");
    cv::imshow("dst image", dst);
    cv::waitKey();
}

