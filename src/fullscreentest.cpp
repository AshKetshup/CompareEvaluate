#include "fullscreentest.h"

FullScreenTest::FullScreenTest(QWidget *parent) : QDialog(parent) {
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setStyleSheet("background-color: black");

    leftImageLabel = new QLabel(this);
    rightImageLabel = new QLabel(this);

    // Set the image alignment to center
    leftImageLabel->setAlignment(Qt::AlignCenter);
    rightImageLabel->setAlignment(Qt::AlignCenter);

    // Set size policy to retain aspect ratio and expand horizontally
    leftImageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    rightImageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(leftImageLabel);
    layout->addWidget(rightImageLabel);
    layout->setContentsMargins(0, 0, 0, 0);

    setLayout(layout);
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

void FullScreenTest::showImages() {
    string left = TestManager::getCurrentTest().getFirst().string();
    string right = TestManager::getCurrentTest().getSecond().string();

    qDebug() << "LEFT : " << left.c_str() ;
    qDebug() << "RIGHT: " << right.c_str();

    QPixmap  leftPixmap( left.c_str());
    QPixmap rightPixmap(right.c_str());

    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    QRect screenGeometry = primaryScreen->geometry();

    // Calculate the available space in the layout
    int availableWidth = screenGeometry.width() / 2; // Divide by 2 for two images
    //int availableHeight = height();

    qDebug() << "leftPixmapSize<"  << leftPixmap.width()   << ", " << leftPixmap.height()   << ">";
    qDebug() << "rightPixmapSize<" << rightPixmap.width()  << ", " << rightPixmap.height()  << ">";
    qDebug() << "availableSize<"   << layout()->parentWidget()->width()   << ", " << layout()->parentWidget()->height()    << ">";

    // Calculate the aspect ratio of each image
    double leftAspectRatio  =  double(leftPixmap.width()) /  leftPixmap.height();
    double rightAspectRatio = double(rightPixmap.width()) / rightPixmap.height();

    qDebug() << "leftAspectRatio : " << leftAspectRatio;

    pair<int, int>  leftSize({ availableWidth,  static_cast<int>(availableWidth / leftAspectRatio ) });
    pair<int, int> rightSize({ availableWidth,  static_cast<int>(availableWidth / rightAspectRatio) });

    qDebug() << "leftSize<"  << leftSize.first  << ", " << leftSize.second  << ">";
    qDebug() << "rightSize<" << rightSize.first << ", " << rightSize.second << ">";

    // Scale images to fit available space while maintaining aspect ratio
    leftImageLabel->setPixmap(  leftPixmap.scaled( leftSize.first, leftSize.second )); //, Qt::KeepAspectRatio
    rightImageLabel->setPixmap(rightPixmap.scaled(rightSize.first, rightSize.second));
}
