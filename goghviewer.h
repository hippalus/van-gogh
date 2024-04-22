#ifndef GOGHVIEWER_H
#define GOGHVIEWER_H

#include "imageloader.h" 
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class GoghViewer;
}
QT_END_NAMESPACE

class GoghViewer : public QMainWindow
{
    Q_OBJECT

public:
    GoghViewer(QWidget *parent = nullptr);
    ~GoghViewer();
    void openImage(QString selectedFile);

private slots:

    void on_pushButton_released();

    void on_action_Open_triggered();

private:
    Ui::GoghViewer *ui;
    ImageLoader il;
    void openImage();
    QPixmap loadImage(QString imagePath);
};
#endif // GOGHVIEWER_H
