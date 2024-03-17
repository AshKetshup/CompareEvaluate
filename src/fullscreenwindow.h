#ifndef FULLSCREENWINDOW_H
#define FULLSCREENWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QKeyEvent>

#include "fullscreentest.h"

class FullScreenWindow : public QDialog {
    Q_OBJECT

public:
    explicit FullScreenWindow(QWidget *parent = nullptr);
    ~FullScreenWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QLabel *messageLabel;
    FullScreenTest *fullScreenTest;
};

#endif // FULLSCREENWINDOW_H
