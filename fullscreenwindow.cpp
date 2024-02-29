#include "fullscreenwindow.h"

FullScreenWindow::FullScreenWindow(QWidget *parent) : QDialog(parent) {
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setStyleSheet("background-color: black;");


    messageLabel = new QLabel("Fullscreen Window", this);
    messageLabel->setAlignment(Qt::AlignCenter);
    messageLabel->setStyleSheet("color: white; font-size: 24px;");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(messageLabel);
    layout->setContentsMargins(0, 0, 0, 0);

    setLayout(layout);
}

FullScreenWindow::~FullScreenWindow() { }

void FullScreenWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Escape:
            close();
            break;
        default:
            QDialog::keyPressEvent(event);
    }
}
