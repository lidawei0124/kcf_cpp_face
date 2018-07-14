void TestWindow::onCatureImage()
{
    // 点击截图按钮开始截图;
    CaptureScreen* captureHelper = new CaptureScreen();
    connect(captureHelper, SIGNAL(signalCompleteCature(QPixmap)), this, SLOT(onCompleteCature(QPixmap)));
    captureHelper->show();
}

void TestWindow::onCompleteCature(QPixmap captureImage)
{
    ui.label->setPixmap(captureImage);
}