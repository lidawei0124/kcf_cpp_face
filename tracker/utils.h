#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "opencv2/opencv.hpp"

using namespace std;

double calc_cmp(cv::Mat &pic1, cv::Mat &pic2);

cv::Rect decode_gt(istringstream &ss, bool mode);
cv::Mat get_feature(cv::Mat &z, bool hog, int cell_size = 4);
void zoom_rect(cv::Rect &rect, float scale);

#endif // UTILS_H
