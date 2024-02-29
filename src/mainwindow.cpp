#include "mainwindow.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDebug>
#include <QLabel>
#include "fullscreenwindow.h"
#include "fullscreentest.h"

MainWindow::MainWindow(QWidget *parent) : QDialog(parent) {
    configLineEdit = new QLineEdit(this);
    projectNameLineEdit = new QLineEdit(this);
    browseButton = new QPushButton("Browse", this);
    beginButton = new QPushButton("Done", this);
    cancelButton = new QPushButton("Cancel", this);
    fullscreentest = new FullScreenTest(this);

    connect(browseButton, &QPushButton::clicked, this, &MainWindow::browseDirectory);
    connect(beginButton, &QPushButton::clicked, this, &MainWindow::begin);
    connect(cancelButton, &QPushButton::clicked, this, &MainWindow::cancel);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(new QLabel("Config File: (*.toml)"), 0, 0);
    layout->addWidget(configLineEdit, 0, 1);
    layout->addWidget(browseButton, 0, 2);
    layout->addWidget(new QLabel("Test Name:"), 1, 0);
    layout->addWidget(projectNameLineEdit, 1, 1, 1, 2);
    layout->addWidget(beginButton, 2, 1, 1, 2, Qt::AlignRight);
    layout->addWidget(cancelButton, 2, 0, 1, 2, Qt::AlignRight);

    setLayout(layout);
}

MainWindow::~MainWindow() {

}

void MainWindow::browseDirectory() {
    QString file = QFileDialog::getOpenFileName(this, tr("Select a Config File"), QDir::homePath());
    if (!file.isEmpty())
        configLineEdit->setText(file);
}

void MainWindow::begin() {
    QString configFile = configLineEdit->text();
    QString projectName = projectNameLineEdit->text();

    qDebug() << "Config File:" << configFile;
    qDebug() << "Project Name:" << projectName;

    accept(); // Close the dialog
    fullscreentest->showFullScreen();
}

void MainWindow::cancel() {
    reject(); // Close the dialog
}
