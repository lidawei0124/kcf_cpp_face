void TestWindow::onCatureImage()
{
    // �����ͼ��ť��ʼ��ͼ;
    CaptureScreen* captureHelper = new CaptureScreen();
    connect(captureHelper, SIGNAL(signalCompleteCature(QPixmap)), this, SLOT(onCompleteCature(QPixmap)));
    captureHelper->show();
}

void TestWindow::onCompleteCature(QPixmap captureImage)
{
    ui.label->setPixmap(captureImage);
}