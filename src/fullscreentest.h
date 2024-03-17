#ifndef FULLSCREENTEST_H
#define FULLSCREENTEST_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QKeyEvent>

#include "testmanager.h"


class FullScreenTest : public QDialog {
    Q_OBJECT

public:
    explicit FullScreenTest(QWidget *parent = nullptr);
    ~FullScreenTest();

    void showImages();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QLabel *leftImageLabel;
    QLabel *rightImageLabel;
    QPixmap leftPixmap;
    QPixmap rightPixmap;
};

#endif // FULLSCREENTEST_H
