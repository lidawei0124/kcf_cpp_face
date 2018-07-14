/*
 * File:   engine.h
 * Author: liuyang
 */

#ifndef Engine_H
#define Engine_H

#include <QObject>
#include <string.h>
#include <opencv2/opencv.hpp>
//#include <cv.hpp>

#include "main/defs.h"
#include "tracker/kcftracker.hpp"
//#include "recognizer/faceRecognizer.h"
//#include "detector/faceDetector.h"

using namespace cv;
using namespace std;

class Engine : public QObject
{
    Q_OBJECT
    KCFTracker * _tracker;
    //MyFaceRecognizer * _recognizer;
    //FaceDetector * _detector;
    Size _face_size;    //the size of face template
    unsigned char _sys_mode;    //system mode, including detection and tracking
    unsigned int _frame_cnt;    //frame count
    vector<string> _training_label; //traing set label
    string _info;       //text info to show in the video

    static const unsigned char DETECTION=0; //sys_mode DETECTION
    static const unsigned char TRACKING=1;  //sys_mode TRACKING
    static const unsigned int DETECTION_STEP = 30;  //frame inteval of detection process

public:
    //face process, including detection, recognize, and tracking
    void process( Mat & frame);
    //sample faces and save them to SAMPLE_PATH. You can use them as the training set.
    void sample_face(Mat &frame);
    //get traing labels of training set
    vector<string> get_training_labels();
    //constructor
    Engine(QObject *parent=0) : QObject(parent)
    {
        _tracker = new KCFTracker();
        //_recognizer = new MyFaceRecognizer();
        //_detector = new FaceDetector();
        _face_size = Size(IMG_WIDTH, IMG_HEIGHT);
        _sys_mode = DETECTION;  //init status is detection.
        _frame_cnt = 0;
    }
    //deconstructor
    virtual ~Engine();
};

#endif // Engine_H
