#-------------------------------------------------
#
# Project created by QtCreator 2017-06-02T10:49:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = tracker_exe

TEMPLATE = app
DESTDIR = $$PWD

#INCLUDEPATH += /usr/local/include/opencv \
#            ./resources
INCLUDEPATH += ./resources

#CONFIG += link_pkgconfig
#PKGCONFIG = opencv

SOURCES +=  tracker/fhog.cpp \
    tracker/kcftracker.cpp \
    main/main.cpp \
    main/mainwindow.cpp \
    main/engine.cpp \
    main/capturescreen.cpp \
    main/run_tracker.cpp \
    tracker/kalman_filter.cpp \
    frame_input/frameinput.cpp

HEADERS  += tracker/ffttools.hpp \
    tracker/fhog.hpp \
    tracker/kcftracker.hpp \
    tracker/labdata.hpp \
    tracker/recttools.hpp \
    tracker/tracker.h \
    main/defs.h \
    main/mainwindow.h \
    main/engine.h \
    main/capturescreen.h \
    main/run_tracker.h \
    tracker/kalman_filter.h \
    frame_input/frameinput.hpp

INCLUDEPATH += /home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/include/opencv \
               /home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/include/opencv2

LIBS += /home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_aruco.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_bgsegm.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_bioinspired.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_calib3d.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_ccalib.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_core.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_cvv.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_datasets.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_dnn.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_dpm.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_face.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_features2d.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_flann.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_fuzzy.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_highgui.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_imgcodecs.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_imgproc.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_line_descriptor.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_ml.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_objdetect.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_optflow.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_photo.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_plot.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_reg.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_rgbd.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_saliency.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_shape.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_stereo.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_stitching.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_structured_light.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_superres.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_surface_matching.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_text.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_tracking.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_videoio.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_video.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_videostab.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_xfeatures2d.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_ximgproc.so \
/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_xobjdetect.so \
#/home/lidawei0124/ti5728sdk/linux-devkit/sysroots/cortexa15hf-vfp-neon-linux-gnueabi/usr/lib/libopencv_xphoto.s

FORMS    +=   main/mainwindow.ui

target.path = /home/root/
INSTALLS += target
