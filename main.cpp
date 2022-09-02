
#include <QApplication>
#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include <QDebug>

#include "mainwin.h"

void updateQSS()
{
    QFile file(":/resources/qss.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        qApp->setStyleSheet(qss);
        file.close();
    }
}

void loadFont()
{
    int fontId = QFontDatabase::addApplicationFont(":/resources/font/LunDao.ttf");
    if (fontId == -1) {
        qDebug("load font failed!");
    }

//    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);//获取字体名称
//    qDebug() << __FUNCTION__ << fontName << "CloudShuiZhu-GB Normal";
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    loadFont();
    updateQSS();

    MainWin w;
    w.show();

    return a.exec();;
}
