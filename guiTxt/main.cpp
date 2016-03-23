#include <QtGui/QApplication>
#include "mainwindow.h"
#include <windows.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

         QPixmap pixmap("C:/MyQT/guiTxt/start.jpg");        //加载图片
         QSplashScreen splash(pixmap);      //构造splash 并显示到屏幕上
         splash.show();                     //显示splash

         Sleep(3000);

         QSound::play("C:/MyQT/guiTxt/李荣浩 - 李白.wav");//这个API接口自动播放音乐

         w.show();
         splash.finish(&w);
         return a.exec();

}
