#include <QtGui/QApplication>
#include "mainwindow.h"
#include <windows.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

         QPixmap pixmap("C:/MyQT/guiTxt/start.jpg");        //����ͼƬ
         QSplashScreen splash(pixmap);      //����splash ����ʾ����Ļ��
         splash.show();                     //��ʾsplash

         Sleep(3000);

         QSound::play("C:/MyQT/guiTxt/���ٺ� - ���.wav");//���API�ӿ��Զ���������

         w.show();
         splash.finish(&w);
         return a.exec();

}
