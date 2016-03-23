#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    this->setWindowTitle("�������");
    this->movie = new QMovie("C:/MyQT/guiTxt/photo.gif");         //��movieʵ����
    this->movie2 = new QMovie("C:/MyQT/guiTxt/panda.gif");        //��movieʵ����

    qDebug()<<"ͼƬ��è����֡��Ϊ��"<<this->movie->frameCount();              //����ͼƬ1��֡��
    qDebug()<<"ͼƬ����֡��Ϊ��"<<this->movie2->frameCount();             //����ͼƬ2��֡��

    ui->movielabel_2->setMovie(this->movie2);                     //����������ʱ��ͼƬ��Ϊ����һ��ͬʱ����
    ui->movielabel->setMovie(this->movie);                        //����������ʱ��ͼƬ��Ϊ����һ��ͬʱ����
    this->movie->start();
    this->movie2->start();

    QObject ::connect(ui->stopButton,SIGNAL(clicked()),this,SLOT(StopSlot()));                  //ֹͣ
    QObject ::connect(ui->continueButton,SIGNAL(clicked()),this,SLOT(ContinueSlot()));          //����
}

about::~about()
{
    delete ui;
}

void about :: StopSlot()
{
    this->movie->stop();        //ֹͣ���� ��è����

    this->movie2->stop();       //ֹͣ���� ����
}

void about :: ContinueSlot()
{
    this->movie->start();       //��ʼ���� ��è����
    this->movie2->start();      //��ʼ���� ����
}
