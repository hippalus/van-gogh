#ifndef GOGHVIEWER_H
#define GOGHVIEWER_H

#include "imageloader.h"
#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui
{
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

    void on_action_Open_triggered();

    void on_btnOpenFile_clicked();

    void on_actionAbout_triggered();

    void on_pushButton_clicked();

    void on_btnToolGreyscale_clicked();

    void on_btnSaveAs_clicked();

private:
    Ui::GoghViewer *ui;
    ImageLoader il;
    QPixmap pm;
    std::unique_ptr<QGraphicsScene> scene;
    void openImage();
    QPixmap loadImage(QString imagePath);
};
#endif // GOGHVIEWER_H
