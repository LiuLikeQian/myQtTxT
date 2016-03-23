#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    this->setWindowTitle("关于软件");
    this->movie = new QMovie("C:/MyQT/guiTxt/photo.gif");         //将movie实例化
    this->movie2 = new QMovie("C:/MyQT/guiTxt/panda.gif");        //将movie实例化

    qDebug()<<"图片熊猫烧香帧数为："<<this->movie->frameCount();              //返回图片1的帧数
    qDebug()<<"图片滑稽帧数为："<<this->movie2->frameCount();             //返回图片2的帧数

    ui->movielabel_2->setMovie(this->movie2);                     //窗口启动的时候图片作为窗口一样同时启动
    ui->movielabel->setMovie(this->movie);                        //窗口启动的时候图片作为窗口一样同时启动
    this->movie->start();
    this->movie2->start();

    QObject ::connect(ui->stopButton,SIGNAL(clicked()),this,SLOT(StopSlot()));                  //停止
    QObject ::connect(ui->continueButton,SIGNAL(clicked()),this,SLOT(ContinueSlot()));          //继续
}

about::~about()
{
    delete ui;
}

void about :: StopSlot()
{
    this->movie->stop();        //停止动画 熊猫烧香

    this->movie2->stop();       //停止动画 滑稽
}

void about :: ContinueSlot()
{
    this->movie->start();       //开始动画 熊猫烧香
    this->movie2->start();      //开始动画 滑稽
}
