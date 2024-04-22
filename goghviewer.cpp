#include "goghviewer.h"
#include "./ui_goghviewer.h"
#include "imageloader.h"

#include <iostream>

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QMessageBox>

GoghViewer::GoghViewer(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GoghViewer)
{
    this->il = ImageLoader();
    ui->setupUi(this);
    ui->gridWidget->hide();
}

GoghViewer::~GoghViewer()
{
    delete ui;
}

void GoghViewer::on_action_Open_triggered()
{
    GoghViewer::openImage();
}

void GoghViewer::on_btnOpenFile_clicked()
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
    ui->imageViewer->setScene(scene);

    QPixmap pixmap = this->il.loadImage(selectedFile);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
    scene->addItem(item);

    this->adjustSize();
}

void GoghViewer::on_actionAbout_triggered()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("About Van Gogh");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(R"(
        🖌️ Van Gogh Image Viewer
        <br/>
        <a href="https://github.com/hdoordt/van-gogh">Git repository</a>
    )");
    msgBox.exec();
}

void GoghViewer::on_pushButton_clicked()
{
    ui->gridWidget->setVisible(!ui->gridWidget->isVisible());
}

void GoghViewer::on_btnToolGreyscale_clicked()
{
    std::cout << "We should probably convert the image to greyscale at some point" << std::endl;
}
