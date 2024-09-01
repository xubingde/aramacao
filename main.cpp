#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFileSystemModel>
#include <QString>
#include <QStringListModel>
#include "main.h"
#include "publictype.h"
#include "mainwindow.h"

int
main(int  argc,
     char **  argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("AraMacao");
    app.setApplicationVersion("0.1.0");

    QFile  qss;
    xu::StyleType  stype = xu::getGuiStyle();
    switch (stype) {
    case xu::StyleType::dark :
        qss.setFileName(":qdarkstyle/dark/darkstyle.qss");
        break;
    case xu::StyleType::light :
        qss.setFileName(":qdarkstyle/light/lightstyle.qss");
        break;
    case xu::StyleType::defaultStyle :
        break;
    }

    qss.open(QFile::ReadOnly);
    QString  styleSheet = QString::fromUtf8(qss.readAll());
    app.setStyleSheet(styleSheet);
    qss.close();

    QTranslator  translator;
    QStringList const  uiLanguages = QLocale::system().uiLanguages();
    for (QString const &  locale : uiLanguages) {
        QString const  baseName = "aramacao" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    xu::MainWindow  w;
    w.show();
    return app.exec();
}
