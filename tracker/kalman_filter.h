#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.hpp>

#include <string>

using namespace std;
using namespace cv;

class MyKalmanFilter
{
public:
	
	void init_kalman_filter(Point init_pos);
	
	/**
     * @brief getCurrentState return the current state of KF
     * @return
     */
    Point getCurrentState() const;

    Point filter(Point measure_pos) ;

    MyKalmanFilter(){};
    ~MyKalmanFilter(){};
private:

	Point KFPredictCenter;
    Point KFCorrectCenter;
    KalmanFilter KF;
    Mat_<float> measurement;

	/* data */
};

#endif
