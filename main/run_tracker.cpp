#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

#include "main/defs.h"
#include "tracker/kcftracker.hpp"
#include "opencv2/opencv.hpp"
#include "frame_input/frameinput.hpp"
//#include "tracker/template_match.hpp"

using namespace cv;
using namespace std;
int detect_or_pick=1;//detect=1,pick=2
static Rect box;
static bool box_flag=false;
static bool rect_ready=false;
static Point origin;
static Mat _src_image;
static Mat img;
double time_cost=0;
static int64 tic, toc;
int nframe=0;//count frame in confidence, init it when tracking failed.
int frames=0;//cound frame of current
double scores[10000];
int failflags[10000];
bool flag = false;
bool a=false, b=false, c=false;
bool end_flag=true;
double mean5,change2point,change3point;
double zero=0.05;//use zero replace 0
double failflag=0.72 ;
int fail_count=0;//if fail_count==5,fail
//when score reduce to failflag*mean5, means fail
int k=2;//k=(0:apce,1:psr,2:peakvalue),confidence methods
//psr zero=5-6,failflag=0.4
//peakvalue zero=0.1 failflag=0.72
//apce zero=2 failflag=0.4


string face_cascade_name = "/home/lidawei0124/qtproject/facedetect/haarcascade_frontalface_alt2.xml";//face
CascadeClassifier face_cascade;//face
vector<Rect> faces;
/************************************************************************************************************************/
/****                            如果采用这个onMouse()函数的话，则可以画出鼠标拖动矩形框的4种情形                        ****/
/************************************************************************************************************************/
void facedetect(cv::Mat &frame)
{
    Mat img_detect=frame;
    Mat img_gray;
    cvtColor(img_detect,img_gray,CV_BGR2GRAY);
    equalizeHist(img_gray,img_gray);
    face_cascade.detectMultiScale(img_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
    //imshow("ss",img_gray);
    //waitkey(1000);
    box=faces[1];
    rect_ready=true;
}

void onMouse(int event,int x,int y,int,void*)
{    
     //Point origin;//不能在这个地方进行定义，因为这是基于消息响应的函数，执行完后origin就释放了，所以达不到效果。     if(box_flag)
    if(box_flag)
    {
        box.x=MIN(origin.x,x);//不一定要等鼠标弹起才计算矩形框，而应该在鼠标按下开始到弹起这段时间实时计算所选矩形框        box.y=MIN(origin.y,y);
        box.y=MIN(origin.y,y);//不一定要等鼠标弹起才计算矩形框，而应该在鼠标按下开始到弹起这段时间实时计算所选矩形框        box.y=MIN(origin.y,y);
        box.width=abs(x-origin.x);//算矩形宽度和高度
        box.height=abs(y-origin.y);
        //box &= Rect(0,0,_src_image.cols,_src_image.rows);//保证所选矩形框在视频显示区域之内
        if(nframe==0)
        {

//            box.x=6;
//            box.y=166;
//            box.width=42;
//            box.height=26;//carscale
//            box.x=213;
//            box.y=121;
//            box.width=21;
//            box.height=95;//woman
//            box.x=23;
//            box.y=88;
//            box.width=66;
//            box.height=55;//car1
//            box.x=478;
//            box.y=143;
//            box.width=80;
//            box.height=111;//car1
            box.x=57;
            box.y=21;
            box.width=31;
            box.height=45;//girl


           // 478	143	80	111


        }
            //test.avi:6,166,42,26
            //woman.avi:213	121	21	95
   }
  if(event==CV_EVENT_LBUTTONDOWN)
    {
        box_flag=true;//鼠标按下的标志赋真值
        origin=Point(x,y);//保存下来单击是捕捉到的点
        box=Rect(x,y,0,0);//这里一定要初始化，宽和高为(0,0)是因为在opencv中Rect矩形框类内的点是包含左上角那个点的，但是不含右下角那个点
    }
    else if(event==CV_EVENT_LBUTTONUP)    
    {
        box_flag=false;
        rect_ready = true;
    }
}
void run_tracker(void)
{
    if(waitKey(5000)==27)
    {
    }
    KCFTracker * _tracker = new KCFTracker();
    //TMTracker * _tracker = new TMTracker(false);
    //CamareInput frame_input(2);//1 should be HDMI input, 2,USB camera input
    //PicInput frame_input("/home/lidawei0124/imagecut/CarScale/img/carscale.txt");
    //PicInput frame_input("/home/lidawei0124/imagecut/Woman/img/woman.txt");
    //PicInput frame_input("/home/lidawei0124/imagecut/Car1/img/car1.txt");
    //PicInput frame_input("/home/lidawei0124/imagecut/Car1/img/car1.txt");
    PicInput frame_input("/home/lidawei0124/imagecut/Girl/img/girl.txt");
    //VideoInput frame_input("/home/lidawei0124/woman.avi");
    //VideoInput frame_input("/home/lidawei0124/test.avi");

    string info;
    float score=0;
    Point text_pos(40, 40);
    //freopen("trackerlog.txt","w",stdout);
    switch (k)
    {
    case 0:cout<<"With confidence method: apce"<<endl;

        break;
    case 1:cout<<"With confidence method: psr"<<endl;

        break;
    case 2:cout<<"Withconfidence method: peakvalue"<<endl;

        break;
    default:cout<<"Without any confidence methods"<<endl;
        break;
    }

    if( !frame_input.next(_src_image) )
    {
        cout << "frame input error!"<<endl;
        return;
    }
    namedWindow("tracking");
    face_cascade.load(face_cascade_name);//load xml

    while(end_flag)
    {
        //printf("pickpickstart\n");
       cout<<"please pick target with your mouse"<<endl<<"press key 'n' go to next frame to start tracking!"<<endl<<"press key 'esc' to quit the tracking!"<<endl;

        flag = true;
        rect_ready=false;

        //捕捉鼠标

        if( !frame_input.init_rect(_src_image) )
        {
            cout<<"input ended!"<<endl;

            return;
        }
        if(detect_or_pick==1)
        facedetect(_src_image);
        else if(detect_or_pick==2)
        setMouseCallback("tracking", onMouse, 0);

        while(!rect_ready)
        {

            Mat frame_buf = _src_image.clone();
            rectangle(frame_buf, box, Scalar(255,0,0), 1,8,0);  //能够实时显示在画矩形窗口时的痕迹
            imshow("tracking", frame_buf);
            if( waitKey(1) == 'n' )//press key "n" go to next frame to start tracking
            {
                end_flag=frame_input.next(_src_image);//false means input end
            }
            else;
        }
        _tracker->init(box, _src_image);
        vector<float> perf(1, 0);
        nframe = 0;
        while(flag&&end_flag)
        {
            a=false;
            b=false;
            c=false;
            end_flag=frame_input.next(_src_image);//false means input end
            nframe++;
            //
            frames++;
            tic = getTickCount();
            box = _tracker->update(_src_image, score, perf);
            toc = cv::getTickCount() - tic;
            time_cost += toc;
            double fps = double(frames) * double(getTickFrequency()) / time_cost;
            info ="frame:" + to_string(frames) + " response:" + to_string(int(1000*score))+ " fps:"+to_string(int(fps))+" psr:" + to_string(perf[1])+"  apce: "+to_string(perf[0]);
            rectangle(_src_image, box, Scalar(0,255,0),1,8,0);  //能够实时显示在画矩形窗口时的痕迹
            putText(_src_image, info, text_pos, CV_FONT_HERSHEY_COMPLEX, 0.4, Scalar(0, 0, 255));
            imshow("tracking", _src_image);

                if (nframe >= 6)
                {
                    mean5=(scores[nframe - 5] + scores[nframe - 4] + scores[nframe - 3] + scores[nframe - 2] + scores[nframe - 1]) / 5;
                    change2point=abs(scores[nframe] - scores[nframe - 1]);
                    change3point=(scores[nframe] + scores[nframe - 2] - 2 * scores[nframe - 1]);
                    if (scores[nframe] <mean5*failflag)
                        a = true;
                    if (change2point<zero)
                        b = true;
                    if (change3point<zero)
                        c = true;
                    if (a&&b&&c||fail_count>=5)
                    {
                        flag = false;
                        printf("failed,%d %d\n",a+b+c,fail_count);
                        fail_count=0;
                        //getchar();
                    }
                }
                cout<<frames<<'\t'<< setw(8)<<fps<<'\t'<< setw(8)<<perf[0]<<'\t'<< setw(8)<<perf[1]<<'\t'<< setw(8)<<perf[2]<<'\t'<<int(box.x)<<'\t'<<int(box.y)<<'\t'<<int(box.width)<<'\t'<<int(box.height)<<'\t'<<a<<'\t'<<b<<'\t'<<c<<'\t'<<a+b+c<<endl;
                //cout<<frames<<'\t'<<"mean5:"<< setw(8)<<mean5<<'\t'<<"2:"<<setw(8)<<change2point<<'\t'<<"3:"<< setw(8)<<change3point<<'\t'<<"psr:"<< setw(8)<<perf[1]<<'\t'<<int(box.x+0.5*box.width)<<'\t'<<int(box.y+0.5*box.height)<<'\t'<<a<<'\t'<<b<<'\t'<<c<<'\t'<<a+b+c<<endl;
            if(waitKey(50)==27)
            {
               end_flag=false;
               break;
            }
            //cout<<end_flag<<endl;
        }
    }
    time_cost = time_cost / double(getTickFrequency());
    double fps = double(frames) / time_cost;
    cout<<"fps: "<<fps<<endl;
}
