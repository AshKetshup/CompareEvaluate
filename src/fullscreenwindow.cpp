#include "fullscreenwindow.h"

FullScreenWindow::FullScreenWindow(QWidget *parent) : QDialog(parent) {
    fullScreenTest = new FullScreenTest(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setStyleSheet("background-color: black;");

    messageLabel = new QLabel(
                "Welcome to the Test.\n"
                "It will be shown 2 similar pictures.\n"
                "\n\n"
                "Please select on a scale from 1-9 how much better the second picture was compared to the first one.\n"
                "Keep in mind that: \n"
                "1 - Left is the best\n"
                "5 - No difference \n"
                "9 - Right is the best", this);
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
        case Qt::Key_Space:
            fullScreenTest->showImages();
            fullScreenTest->showFullScreen();
            close();
            break;
        default:
            QDialog::keyPressEvent(event);
    }
}
