#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include "fullscreenwindow.h"
#include "fullscreentest.h"

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void browseDirectory();
    void begin();
    void cancel();

private:
    QLineEdit *configLineEdit;
    QLineEdit *projectNameLineEdit;
    QPushButton *browseButton;
    QPushButton *beginButton;
    QPushButton *cancelButton;
    FullScreenWindow *fullScreenWindow;
    FullScreenTest *fullscreentest;

};

#endif // MAINWINDOW_H
