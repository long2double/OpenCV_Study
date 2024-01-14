#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    Mat img = imread("/home/long2double/Downloads/1.jpg");
    imshow("img", img);
    waitKey();
}
