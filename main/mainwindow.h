#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QPaintEvent>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QImage>
#include <QThread>
#include <opencv2/opencv.hpp>

#include "ui_mainwindow.h"
#include "engine.h"

using namespace std;
using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void onCatureImage();
    void onCompleteCature(QPixmap captureImage);

    ~MainWindow();

public slots:
    void updateImage();
    void run_engine();
    void sample_faces();

private:

    QTimer _timer;
    Mat _src_image;
    VideoCapture _video_cap;

    QLabel *imageLabel;
    Ui::MainWindow *ui;
    Engine* _engine;
    QThread _engine_thread;
    bool _process_flag;
    bool _sample_flag;
protected:
    void paintEvent(QPaintEvent *e);
};

#endif // MAINWINDOW_H
