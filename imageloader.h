#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <qstring.h>
#include <qpixmap.h>

class ImageLoader
{
public:
    ImageLoader();
    QPixmap loadImage(QString imagePath);

private:
    static void cleanupPngData(void *info);
};

#endif // IMAGELOADER_H