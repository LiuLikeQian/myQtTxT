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

#include <QCloseEvent>  // 当程序关闭的时候 所要处理的内容  所有时间都是protected的

#include <QTextImageFormat>//插入图片需要用到

#include <QTextDocument>  //把图片添加到到缓存中需要用到

//QWidget closeevent QMainWindow closeevent();都有close的例子可到help中查看


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
    void dragEnterEvent(QDragEnterEvent *); //拖动进入事件(开始拖动，先判断是否包含有移动的类型)
    void dropEvent(QDropEvent *);           //放下事件 (放下图片,创建新的图片放到光标处)

    void dragMoveEvent(QDragMoveEvent *);     //拖动事件(拖动过程)
    void mousePressEvent(QMouseEvent *);    //鼠标按下事件 ,为拖动图片做准备，将图片数据放到自定义MIME类型中
    void dropPhotoEvent(QDropEvent *);
private:
    Ui::MainWindow *ui;
    QString saveFileName;
    bool readFile(const QString &fileName);

private slots:
    void newFileSlot();     //新建
    void openFileSlot();    //打开
    void saveAsFileSlot();  //另存
    void saveFileSlot();    //保存
    void prinfFileSlot();   //打印
    void fontFileSlot();    //字体
    void ExitFileSlot();    //退出


    void ColorFileSlot();   //颜色



    void HelpFileSlot();    //帮助
    //void AboutAppActionSlot();   //关于

    /*
    void RedoFileSlot();    //重做
    void UndoFileSlot();    //撤销
    void CutFileSlot();     //剪切
    void CopyFileSlot();    //复制
    void PasteFileSlot();   //粘贴
    void DeleteFileSlot();  //删除
    void SeletAllFileSlot();//全选
    */
    //   void FindFileSlot();    //查找
    //   void InsteadFileSlot(); //替换
    void DatetimeFileSlot();  //时间/日期

    void ServiceActionSlot(); //桌面服务

    void aboutSoftwareSlot();    //子对话框 关于软件

    void inserPhotoSlot();

};


#endif // MAINWINDOW_H
