#include "mainwidget.h"

#include <QApplication>
#include <QFile>

// 通过文件加载样式
void loadStyle() {
    QFile style(":/style.qss");
    if (style.open(QFile::ReadOnly)) {
        QString styleSheet = style.readAll();
        qApp->setStyleSheet(styleSheet);
        style.close();
    }
}

int main(int argc, char *argv[])
{
    // 支持高分辨率屏幕
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
        QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    #endif

    QApplication a(argc, argv);

    loadStyle();

    MainWidget w;
    w.show();
    return a.exec();
}
