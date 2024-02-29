#ifndef FULLSCREENTEST_H
#define FULLSCREENTEST_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QKeyEvent>


class FullScreenTest : public QDialog {
    Q_OBJECT
public:
    explicit FullScreenTest(QWidget *parent = nullptr);
    ~FullScreenTest();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QLabel *leftImageLabel;
    QLabel *rightImageLabel;
    QPixmap leftPixmap;
    QPixmap rightPixmap;

    void showImages();
};

#endif // FULLSCREENTEST_H
