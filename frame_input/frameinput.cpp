#include "frameinput.hpp"
#include <iostream>
#include <stdexcept>

bool PicInput::next(Mat &frame)
{
    if( !getline( _list_file, _frame_name) )
    {
        return false;
    }
    try
    {
        frame = imread(_frame_name, CV_LOAD_IMAGE_COLOR);
    }
    catch (const runtime_error &e)
    {
        // Error handling.
        std::cout<< e.what() << endl;
        return false;
    }
    return true;
}

bool PicInput::init_rect(cv::Mat &frame)
{
    return true;
}

bool VideoInput::next(Mat &frame)
{
    try
    {
        *_p_video_cap>>frame;
    }
    catch (const runtime_error &e)
    {
        // Error handling.
        std::cout<< e.what() << endl;
        return false;
    }
    if(frame.empty())
    {
        return false;
    }
    return true;
}

bool VideoInput::init_rect(cv::Mat &frame)
{
    //return this->next(frame);
    return true;
}

bool CamareInput::next(Mat &frame)
{
    try
    {
        *_p_video_cap>>frame;
    }
    catch (const runtime_error &e)
    {
        // Error handling.
        std::cout<< e.what() << endl;
        return false;
    }
    if(frame.empty())
    {
        return false;
    }
    return true;
}

bool CamareInput::init_rect(cv::Mat &frame)
{
    return this->next(frame);
}
