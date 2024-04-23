#include "goghviewer.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <iostream>
#include <librembrandt/lib.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages)
    {
        const QString baseName = "Van_Gogh_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            a.installTranslator(&translator);
            break;
        }
    }
    GoghViewer w;

    if (argc >= 2)
    {
        w.openImage(QString(argv[1]));
    }
    std::cout << "added: " << rb_add(1, 2) << std::endl;

    w.show();
    return a.exec();
}
