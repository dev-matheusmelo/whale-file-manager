#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString arg_path;
    if(argc >= 1){
        QFileInfo info(argv[1]);
        if(info.isDir()){
            arg_path = argv[1];
        }else{
            arg_path = QDir::homePath();
        }
    }else{
        arg_path = QDir::homePath();
    }

    MainWindow w(nullptr,arg_path);
    w.show();
    return a.exec();
}
