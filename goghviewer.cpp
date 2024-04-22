#include "goghviewer.h"
#include "./ui_goghviewer.h"
#include "imageloader.h"

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <iostream>
#include <string>
#include <fstream>


GoghViewer::GoghViewer(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GoghViewer)
{
    this->il = ImageLoader();
    ui->setupUi(this);
}

GoghViewer::~GoghViewer()
{
    delete ui;
}

void GoghViewer::on_pushButton_released()
{
    GoghViewer::openImage();
}

void GoghViewer::on_action_Open_triggered()
{
    GoghViewer::openImage();
}

void GoghViewer::openImage()
{
    QString selectedFile = QFileDialog::getOpenFileName(this, QString("Select Image File"), NULL, QString("Image Files (*.png *.jpg *.bmp)"));
    GoghViewer::openImage(selectedFile);
}

void GoghViewer::openImage(QString selectedFile)
{
    if (selectedFile.isNull())
    {
        std::cout << "No file selected" << std::endl;
        return;
    }

    std::cout << "Opening image: " << selectedFile.toStdString() << std::endl;

    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    QPixmap pixmap = this->il.loadImage(selectedFile);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
    scene->addItem(item);
}
