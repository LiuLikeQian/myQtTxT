#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMessageBox>
#include <QtDebug>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QTextCodec>
#include <QProcess>
#include <QColorDialog>

#include <QPalette>
#include <QLabel>
#include <QGraphicsTextItem>
#include <QFontDialog>

#include <QUrl>
#include <QDesktopServices>

#include <QImageReader>
#include <QTextDocument>
#include <QDropEvent>
#include <QEvent>
#include <QTextEdit>
#include <QDateTime>
#include <QString>

#include <QSplashScreen>
#include <QPixmap>

#include <QDataStream>
#include "about.h"
#include "qpainter.h"

#include <QCloseEvent>  // ������رյ�ʱ�� ��Ҫ���������  ����ʱ�䶼��protected��

#include <QTextImageFormat>//����ͼƬ��Ҫ�õ�

#include <QTextDocument>  //��ͼƬ��ӵ�����������Ҫ�õ�

//QWidget closeevent QMainWindow closeevent();����close�����ӿɵ�help�в鿴


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event);
    //void insertImage();
    void dragEnterEvent(QDragEnterEvent *); //�϶������¼�(��ʼ�϶������ж��Ƿ�������ƶ�������)
    void dropEvent(QDropEvent *);           //�����¼� (����ͼƬ,�����µ�ͼƬ�ŵ���괦)

    void dragMoveEvent(QDragMoveEvent *);     //�϶��¼�(�϶�����)
    void mousePressEvent(QMouseEvent *);    //��갴���¼� ,Ϊ�϶�ͼƬ��׼������ͼƬ���ݷŵ��Զ���MIME������
    void dropPhotoEvent(QDropEvent *);
private:
    Ui::MainWindow *ui;
    QString saveFileName;
    bool readFile(const QString &fileName);

private slots:
    void newFileSlot();     //�½�
    void openFileSlot();    //��
    void saveAsFileSlot();  //���
    void saveFileSlot();    //����
    void prinfFileSlot();   //��ӡ
    void fontFileSlot();    //����
    void ExitFileSlot();    //�˳�


    void ColorFileSlot();   //��ɫ



    void HelpFileSlot();    //����
    //void AboutAppActionSlot();   //����

    /*
    void RedoFileSlot();    //����
    void UndoFileSlot();    //����
    void CutFileSlot();     //����
    void CopyFileSlot();    //����
    void PasteFileSlot();   //ճ��
    void DeleteFileSlot();  //ɾ��
    void SeletAllFileSlot();//ȫѡ
    */
    //   void FindFileSlot();    //����
    //   void InsteadFileSlot(); //�滻
    void DatetimeFileSlot();  //ʱ��/����

    void ServiceActionSlot(); //�������

    void aboutSoftwareSlot();    //�ӶԻ��� �������

    void inserPhotoSlot();

};


#endif // MAINWINDOW_H
