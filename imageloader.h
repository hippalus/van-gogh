#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QString>
#include <QImage>

class ImageLoader
{
public:
    ImageLoader();
    QImage loadImage(QString imagePath);
    void storeImage(QImage image, QString imagePath);

private:
    static void cleanupPngData(void *info);
};

#endif // IMAGELOADER_H