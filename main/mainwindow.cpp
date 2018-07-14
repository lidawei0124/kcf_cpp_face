#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "defs.h"
#include "capturescreen.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //setup UI
    ui->setupUi(this);
    //the the Label for video
    imageLabel = new QLabel(this);
    //imageLabel->setSizePolicy(Fixed, Fixed);
    ui->verticalLayout->addWidget(imageLabel);
    if(_video_cap.open(CAMERA_INDEX))
    {
        _src_image = Mat::zeros( _video_cap.get(CV_CAP_PROP_FRAME_HEIGHT), _video_cap.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC3);
        _timer.start(TIME_INTEVAL);
    }

    //init values
    _process_flag = false;
    _sample_flag = false;

    _engine = new Engine();
    _engine_thread.start();
    _engine->moveToThread(&_engine_thread);

    //connect signals and slots
    connect(ui->p_btn_run, SIGNAL(clicked()),
                     this, SLOT(run_engine()));
    connect(ui->p_btn_sample, SIGNAL(clicked()),
                     this, SLOT(sample_faces()));
    connect(&_timer, &QTimer::timeout, this, &MainWindow::updateImage);

    //show ID of training set in Qt GUI
    /*
    vector<string> name_list = _engine->get_training_labels();
    string name_str;
    for(int i=0; i<name_list.size(); i++)
    {
        name_str += name_list[i] + "\n";
    }
    ui->t_names->setText(name_str.c_str());
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::run_engine()
{
    if(_process_flag)
    {
        _process_flag = false;
        ui->p_btn_run->setText("start");
    }
    else
    {
        _process_flag = true;
        ui->p_btn_run->setText("stop");
    }
}

void MainWindow::sample_faces()
{
    if(_sample_flag)
    {
        _sample_flag = false;
        ui->p_btn_sample->setText("sample");
    }
    else
    {
        _sample_flag = true;
        ui->p_btn_sample->setText("process");
    }
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    //draw image
    QPainter painter(this);
    QImage image1 = QImage((uchar*)(_src_image.data), _src_image.cols, _src_image.rows, QImage::Format_RGB888);
    painter.drawImage(QPoint(20,20), image1);
}

//timeout slot, each TIME_INTEVAL run once
void MainWindow::updateImage()
{
    _video_cap>>_src_image;
    //std::cout<<"cols: "<<_src_image.cols<< "rows:" << _src_image.rows <<std::endl;
    if(_src_image.data)
    {
        if(_process_flag)
        {
            if(_sample_flag)
            {
                _engine->sample_face(_src_image);
            }
            else
            {
                _engine->process(_src_image);
            }
        }
        cvtColor(_src_image, _src_image, CV_BGR2RGB);//convert format
        this->update();
    }
}

void MainWindow::onCatureImage()
{
    CaptureScreen* captureHelper = new CaptureScreen(this);
    connect(captureHelper, SIGNAL(signalCompleteCature(QPixmap)), this, SLOT(onCompleteCature(QPixmap)));
    captureHelper->show();
}

void MainWindow::onCompleteCature(QPixmap captureImage)
{
    ui->label->setPixmap(captureImage);
}
