#include "fullscreentest.h"

FullScreenTest::FullScreenTest(QWidget *parent) : QDialog(parent) {
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setStyleSheet("background-color: gray");

    leftImageLabel = new QLabel(this);
    rightImageLabel = new QLabel(this);
    //leftImageLabel->setAlignment(Qt::AlignLeft);
    //rightImageLabel->setAlignment(Qt::AlignRight);

    leftImageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    rightImageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    QGridLayout *layout = new QGridLayout(this);

    layout->addWidget(leftImageLabel, 0, 1, Qt::AlignLeft);
    layout->addWidget(rightImageLabel, 0, 2, Qt::AlignRight);
    //layout->setColumnStretch(0,1);
    //layout->setColumnStretch(1,1);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);


    leftPixmap.load("C:/Users/User/OneDrive/scool stuff/multimedia/test/test1/rainbow1.jpg");
    rightPixmap.load("C:/Users/User/OneDrive/scool stuff/multimedia/test/test1/colors.jpg");
    leftImageLabel->setPixmap(leftPixmap);
    rightImageLabel->setPixmap(rightPixmap);

    if (leftImageLabel->pixmap().isNull())
        qDebug() << "Error loading left image";
    if (rightImageLabel->pixmap().isNull())
        qDebug() << "Error loading right image";
    qDebug() << "test";
}


FullScreenTest::~FullScreenTest() { }

void FullScreenTest::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_U:
        close();
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}

