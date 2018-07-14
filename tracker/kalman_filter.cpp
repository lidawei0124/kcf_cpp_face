#include "kalman_filter.h"
#include<iostream>
void MyKalmanFilter::init_kalman_filter(Point init_pos)
{
    const int stateNum = 4;
    const int measureNum = 2;

    Mat statePost = (Mat_<float>(stateNum, 1) <<init_pos.x, init_pos.y, 0, 0);
    Mat transitionMatrix = (Mat_<float>(stateNum, stateNum) << 1, 0, 1, 0,
                            0, 1, 0, 1,
                            0, 0, 1, 0,
                            0, 0, 0, 1);

    KF.init(stateNum, measureNum);

    KF.transitionMatrix = transitionMatrix;
    KF.statePost = statePost;
    setIdentity(KF.measurementMatrix);
    setIdentity(KF.processNoiseCov, Scalar::all(1e-1));
    setIdentity(KF.measurementNoiseCov, Scalar::all(1e-3));
    setIdentity(KF.errorCovPost, Scalar::all(0.1));

    measurement = Mat::zeros(measureNum, 1, CV_32F);
}

Point MyKalmanFilter::getCurrentState() const
{
    Mat statePost = KF.statePost;
    return Point(statePost.at<float>(0), statePost.at<float>(1));
}

Point MyKalmanFilter::filter(Point measure_pos) {
    /*
    * do kalman prediction
    */
    KF.predict();
    KFPredictCenter = getCurrentState();

    /*
    * set measurement
    */
    measurement.at<float>(0) = measure_pos.x;
    measurement.at<float>(1) = measure_pos.y;

    /*
    * do kalman correction
    */
    KF.correct(measurement);
    KFCorrectCenter = getCurrentState();
    //std::cout<<"speed x: "<<KF.statePost.at<float>(2)<<" y: " <<KF.statePost.at<float>(3)<<endl;
    return KFCorrectCenter;
}
