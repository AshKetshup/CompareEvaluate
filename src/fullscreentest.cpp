#include "fullscreentest.h"

FullScreenTest::FullScreenTest(QWidget *parent) : QDialog(parent) {
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setStyleSheet("background-color: black");

    leftImageLabel = new QLabel(this);
    rightImageLabel = new QLabel(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(leftImageLabel);
    layout->addWidget(rightImageLabel);
    layout->setContentsMargins(0, 0, 0, 0);

    setLayout(layout);

    leftPixmap.load("");
    rightPixmap.load("");
}


FullScreenTest::~FullScreenTest() { }

void FullScreenTest::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Escape:
        close();
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}

