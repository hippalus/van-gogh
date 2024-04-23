#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <qstring.h>
#include <qimage.h>

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