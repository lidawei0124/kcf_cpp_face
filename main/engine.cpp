/*
 * File:   engine.cpp
 * Author: liuyang
 */
#include "engine.h"

Engine::~Engine()
{

}

//face process , including face detection, recognize and tracking.
void Engine::process(Mat &frame)
{
    Mat grey_image;
    cvtColor(frame, grey_image, CV_BGR2GRAY);
    equalizeHist(grey_image, grey_image);
    vector<Rect> faces;
    vector<string> names;
    Point text_pos(frame.rows*0.1, frame.cols*0.1);
    Rect init_rect(200, 200, 100, 100);

    //Detect mode
    if( DETECTION == _sys_mode )
    {
        /*_detector->detect_face(frame, faces);
        if(faces.size() > 0)
        {
            _recognizer->rec15:27:15: Uploading file "/root/workspace/face_prj/face_detect_recognize_track"...
ognize_face(frame, faces, names);
            _tracker->init(faces[0], frame);
            _sys_mode = TRACKING;//change to track
            _info = names[0];
            names.clear();
        }
        else
        {
            _info ="no person";
        }
        */
        _tracker->init(init_rect, frame);
        _sys_mode = TRACKING;//change to track
    }
    //TRACKING Mode
    else
    {
        Rect result;
        float score;
        vector<float> perf(1, 0);

        result = _tracker->update(frame, score, perf);
        result &= Rect(0, 0, frame.cols, frame.rows);   //constrain result coordinary
        rectangle(frame, result, Scalar( 0, 255, 255 ));
    }
    _frame_cnt ++;
    //each detection step, run detection once
    if( _frame_cnt == 1 )
    {
        _sys_mode = DETECTION;
    }
    else
    {

    }
    //show frame count and system status
    string info_show = to_string(_frame_cnt) + _info;
    putText(frame, info_show, text_pos, CV_FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 255));
}

//sample faces and save them to SAMPLE_PATH. You can use them as training set.
void Engine::sample_face(Mat &frame)
{/*
    Mat grey_image;
    cvtColor(frame, grey_image, CV_BGR2GRAY);
    equalizeHist(grey_image, grey_image);
    vector<Rect> faces;
    Mat face_tmp;
    Point text_pos(frame.rows*0.1, frame.cols*0.1);
    _detector->detect_face(frame, faces);
    for(int i=0; i<faces.size(); i++)
    {
        face_tmp = frame(faces[i]);
        resize(face_tmp, face_tmp, _face_size);
        string img_path = SAMPLE_PATH + to_string(_frame_cnt) + ".jpg";
        imwrite( img_path, face_tmp );
        _frame_cnt ++;
        rectangle(frame, faces[i], Scalar( 0, 255, 0 ));
        _info = "sampling";
    }
    string info_show = to_string(_frame_cnt) + _info;
    putText(frame, info_show, text_pos, CV_FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 0));
    */
}


vector<string> Engine::get_training_labels()
{
    //return _recognizer->get_training_labels();
}
