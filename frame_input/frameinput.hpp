#ifndef FRAMEINPUT_H
#define FRAMEINPUT_H

#include <cv.hpp>
#include <fstream>

using namespace  std;
using namespace cv;

class FrameInput
{
public:
    FrameInput(){};
    virtual bool next(cv::Mat &frame) = 0;
    virtual bool init_rect(cv::Mat &frame) = 0;
    virtual ~FrameInput(){};
};

class PicInput : public FrameInput
{
public:
    PicInput (string pic_path):_pic_path(pic_path) {
        _list_file.open(pic_path, std::ifstream::in);
    }
    virtual bool next(cv::Mat &frame);
    bool init_rect(cv::Mat &frame);
private:
    string _pic_path;
    ifstream _list_file;
    string _frame_name;
};

class VideoInput : public FrameInput
{
public:
    VideoInput (string video_path):_video_path(video_path)
    {
        _p_video_cap = new VideoCapture(_video_path);
    }
    virtual bool next(cv::Mat &frame);
    bool init_rect(cv::Mat &frame);

private:
    string _video_path;
    VideoCapture *_p_video_cap;
};

class CamareInput : public FrameInput
{
public:
    CamareInput (int camera_idx):_camera_idx(camera_idx)
    {
        _p_video_cap = new VideoCapture(_camera_idx);
    }
    virtual bool next(cv::Mat &frame);
    bool init_rect(cv::Mat &frame);
private:
    int _camera_idx;
    VideoCapture *_p_video_cap;
};


#endif // FRAMEINPUT_H
