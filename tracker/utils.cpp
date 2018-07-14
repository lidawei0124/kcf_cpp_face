#include "utils.h"

#include "opencv2/opencv.hpp"
#include "tracker/fhog.hpp"
#include "tracker/recttools.hpp"

using namespace std;
using namespace cv;

double calc_cmp(Mat &pic1, Mat &pic2)
{

    int histSize = 128;

    float range[] = {0,256};
    const float* histRange = {range};
    bool uniform = true; bool accumulate = false;
    Mat pic1_gray, pic2_gray;
    if(pic1.channels() == 3)
    {
       cvtColor(pic1, pic1_gray, CV_RGB2GRAY);
    }
    else
    {
       pic1_gray = pic1;
    }
    if(pic2.channels() == 3)
    {
       cvtColor(pic2, pic2_gray, CV_RGB2GRAY);
    }
    else
    {
       pic2_gray = pic2;
    }
    Mat hist1, hist2;


    calcHist(&pic1_gray,1,0,Mat(),hist1,1,&histSize,&histRange,uniform,accumulate);
    calcHist(&pic2_gray,1,0,Mat(),hist2,1,&histSize,&histRange,uniform,accumulate);

    //double com = compareHist(hist1, hist2, CV_COMP_CORREL);
    //std::cout<< "CV_COMP_CORREL: " << com<<endl;

    double com = compareHist( hist1, hist2, CV_COMP_BHATTACHARYYA);
    //std::cout<< "CV_COMP_BHATTACHARYYA: " << com<<endl;
    return com;
}

//对rect对象进行缩放，
void zoom_rect(Rect &rect, float scale)
{
	Rect tmp = rect;
	rect.width = tmp.width * scale + 0.5;
	rect.height = tmp.height * scale + 0.5;
	rect.x = tmp.x - (rect.width - tmp.width)/2;
	rect.y = tmp.y - (rect.height - tmp.height)/2;
}

//decode ground_truth
Rect decode_gt(istringstream &ss, bool dot)
{
    float xMin, yMin, width, height;
    char tmp;

    if(dot)
    {
        ss >> xMin >> tmp >>  yMin >> tmp >>width >> tmp >> height;
    }
    else
    {
        ss >> xMin >> yMin >> width >> height;
    }
    return Rect(xMin, yMin, width, height);
}

Mat get_feature(Mat &z, bool hog, int cell_size)
{
    Mat FeaturesMap;
    IplImage z_ipl = z;
    CvLSVMFeatureMapCaskade *map;
    int size_patch[3];
    if(hog)
    {
        getFeatureMaps(&z_ipl, cell_size, &map);
        normalizeAndTruncate(map,0.2f);
        PCAFeatureMaps(map);

        size_patch[0] = map->sizeY;
        size_patch[1] = map->sizeX;
        size_patch[2] = map->numFeatures;

        FeaturesMap = cv::Mat(cv::Size(map->numFeatures,map->sizeX*map->sizeY), CV_32F, map->map);  // Procedure do deal with cv::Mat multichannel bug
        FeaturesMap = FeaturesMap.t();
        freeFeatureMapObject(&map);
    }
    else
    {
        FeaturesMap = RectTools::getGrayImage(z);
        FeaturesMap -= (float) 0.5; // In Paper;
        size_patch[0] = z.rows;
        size_patch[1] = z.cols;
        size_patch[2] = 1;
    }
}
