#include "goghviewer.h"
#include "./ui_goghviewer.h"
#include "imageloader.h"

#include <iostream>
#include <memory>

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QColorTransform>
#include <QColor>

#include <librembrandt/proc.h>
#include <rust/cxx.h>

GoghViewer::GoghViewer(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GoghViewer)
{
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
    
    this->setShownImage(QPixmap::fromImage(il.loadImage(selectedFile)));

    adjustSize();
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
    adjustSize();
}

void GoghViewer::on_btnToolGreyscale_clicked()
{
    using namespace rb;
    if (pm.isNull())
    {
        return;
    }

    QImage image = pm.toImage();

    // Could also use constBits, but that doesn't ensure ownership of the bits
    //  https://doc.qt.io/qt-6/implicit-sharing.html
    const uchar *imageDataBuf = image.constBits();

    auto imageBuf = rust::Slice(imageDataBuf, image.sizeInBytes());
    ImageRgbaRef rb_image = create_image_ref(imageBuf, image.width(), image.height());

    // Make sure new_image does not get dropped before new_qimage does,
    // as that would introduce a dangling pointer. An alternative is to
    // provide mechanics for the QImage's cleanupFunction to control when new_image
    // gets dropped.
    ImageLuma new_image = image_make_greyscale(rb_image);
    auto new_image_data = (uchar *)new_image.data.data();
    auto new_qimage = QImage(new_image_data, new_image.width, new_image.height, QImage::Format_Grayscale8);

    this->setShownImage(QPixmap::fromImage(new_qimage));
}

void GoghViewer::on_btnSaveAs_clicked()
{
    if (pm.isNull())
    {
        return;
    }

    QString safeFileName = QFileDialog::getSaveFileName(this, QString("Save Image File"), QString("/home/Pictures/"), tr("Images (*.png *.xpm *.jpg)"));

    QImage image = pm.toImage();

    il.storeImage(image, safeFileName);
}
void GoghViewer::on_dialHueRotate_valueChanged(int value)
{
    std::cout << "HueRotate value changed: " << value << std::endl;
}

void GoghViewer::setShownImage(QPixmap pixmap) {
    pm = pixmap;
    scene = std::unique_ptr<QGraphicsScene>(new QGraphicsScene);
    ui->imageViewer->setScene(scene.get());
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pm);
    scene->addItem(item);
}
