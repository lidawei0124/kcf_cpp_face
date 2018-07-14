/* 
 * File:   defs.h
 * Discription: This file is the config file of this project
 * Author: liuyang
 */

#ifndef DEFS_H
#define	DEFS_H

/** Path: **/
#define FACE_CASCADE_PATH 	"resources/haarcascade_frontalface_default.xml"
#define EYE_CASCADE_PATH 	"resources/haarcascade_eye.xml"
#define TRAINING_LIST   "resources/training_set/list"
#define TEST_LIST       "resources/test_set/list"
#define SAMPLE_PATH "resources/training_set/sample/"

#define TIME_INTEVAL 0
#define CAMERA_INDEX 3

/** image size **/
#define IMG_WIDTH   150
#define IMG_HEIGHT   150

/** Colors... **/
#define NO_MATCH_COLOR    Scalar(0,0,255) //red
#define MATCH_COLOR       Scalar(225,255,0) //yello

/** Face _detector: **/
#define DET_SCALE_FACTOR    1.1
#define DET_MIN_NEIGHBORS   2
#define DET_FLAG            (0|CV_HAAR_SCALE_IMAGE)

/** LBPH face _recognizer: **/
#define LBPH_RADIUS    3
#define LBPH_NEIGHBORS 8
#define LBPH_GRID_X    8
#define LBPH_GRID_Y    8
#define LBPH_THRESHOLD 180.0

#endif	/* DEFS_H */
