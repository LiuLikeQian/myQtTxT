#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

        //获取系统编码，当输出中文的时候不会乱码！！记得包含头文件#include <QTextCodec>后面出现的中文都不会乱码了！！
        QTextCodec *codec = QTextCodec::codecForName("System");              //获取系统编码
        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForCStrings(codec);


        //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

        QTextCodec::setCodecForTr(codec);

        this->setWindowTitle("文本文档.txt");//设置标题

        //设置信号与连接槽   this表示当前对象和地址
        QObject::connect(ui->NewAction,SIGNAL(triggered()),this,SLOT(newFileSlot()));       //新建
        QObject::connect(ui->OpenAction,SIGNAL(triggered()),this,SLOT(openFileSlot()));     //打开
        QObject::connect(ui->SaveAction,SIGNAL(triggered()),this,SLOT(saveFileSlot()));     //保存
        QObject::connect(ui->SaveAsAction,SIGNAL(triggered()),this,SLOT(saveAsFileSlot())); //另存
        QObject::connect(ui->PrintfAction,SIGNAL(triggered()),this,SLOT(prinfFileSlot()));  //打印
        QObject::connect(ui->ExitAction,SIGNAL(triggered()),this,SLOT(ExitFileSlot()));     //退出

        QObject ::connect(ui->UndoAction,SIGNAL(triggered()),ui->textEdit,SLOT(undo()));    //编辑
        QObject ::connect(ui->fontAction,SIGNAL(triggered()),this,SLOT(fontFileSlot()));    //字体
        QObject ::connect(ui->ColorAction,SIGNAL(triggered()),this,SLOT(ColorFileSlot()));  //颜色

        QObject ::connect(ui->RedoAction,SIGNAL(triggered()),ui->textEdit,SLOT(redo()));    //重做

        QObject ::connect(ui->AboutAction,SIGNAL(triggered()),qApp,SLOT(aboutQt()));        //关于 qApp是独特的全局应用对象  相当于指针的qcoreapplication返回
        QObject ::connect(ui->HelpAction,SIGNAL(triggered()),this,SLOT(HelpFileSlot()));    //帮助

        QObject ::connect(ui->CutAction,SIGNAL(triggered()),ui->textEdit,SLOT(cut()));                    //剪切
        QObject ::connect(ui->CopyAction,SIGNAL(triggered()),ui->textEdit,SLOT(copy()));                  //复制
        QObject ::connect(ui->PasteAction,SIGNAL(triggered()),ui->textEdit,SLOT(paste()));                //粘贴
        //QObject ::connect(ui->DeleteAction,SIGNAL(triggered()),ui->textEdit,SLOT(DeletFileSlot()));     //删除
        //QObject ::connect(ui->FindAction,SIGNAL(triggered()),ui->textEdit,SLOT(FindFileSlot()));        //查找
        //QObject ::connect(ui->InsteadAction,SIGNAL(triggered()),ui->textEdit,SLOT(InsteadFileSlot()));  //替换
        QObject ::connect(ui->SelectAllAction,SIGNAL(triggered()),ui->textEdit,SLOT(selectAll()));        //全选
        QObject ::connect(ui->DatetimeAction,SIGNAL(triggered()),this,SLOT(DatetimeFileSlot()));          //日期/时间

        QObject ::connect(ui->ServiceAction,SIGNAL(triggered()),this,SLOT(ServiceActionSlot()));          //桌面服务


        QObject ::connect(ui->AboutAppAction,SIGNAL(triggered()),this,SLOT(aboutSoftwareSlot()));            //子对话框
}


void MainWindow :: closeEvent(QCloseEvent* event)
{

    //event->ignore();        //点击退出  这个事件会被忽略不理 关闭不了了！
    //event->accept();          //点击退出  直接接受了  默认是接收的=。=
  
        /*int index = MessageBox::information(this,"提示","当前文件信息已经改变，是否要保存当前文件？",tr("Yes"),tr("No"));

        if(index == tr("Yes"))
        {
            this->saveFileSlot();
        }*/
        /*

 QMessageBox msgBox;                                                                        //声明消息盒对象

 msgBox.setText("The document has been modified.");                                         //设置消息标题
 msgBox.setInformativeText("Do you want to save your changes?");                            //设置消息内容
 msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel); //设置按钮Save Discard Cancel
 msgBox.setDefaultButton(QMessageBox::Save);                                                //设置默认按钮是Save  即按回车就默认打了Sace
 int ret = msgBox.exec();                                                                   //返回用户选择的按钮

 switch (ret) {
   case QMessageBox::Save:
       this->saveFileSlot();
       break;
   case QMessageBox::Discard:
       event->accpect();
       break;
   case QMessageBox::Cancel:
       event->ignore();
       break;
   default:
       // should never be reached
       break;
 }

        */ 
		if(ui->textEdit->document()->isModified())
    {
        int index = QMessageBox::information(this,"提示","当前文件信息已经改变，是否要保存当前文件？",QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

        if(index == QMessageBox::Yes)
        {
            this->saveFileSlot();
        }
        else if(index == QMessageBox::No)
        {
            event->accept();
        }
        else if(index == QMessageBox::Cancel)
        {
            event->ignore();
        }
    }
    else
    {
        qDebug()<<"程序关闭";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow :: newFileSlot()//new槽
{
    if(ui->textEdit->document()->isModified())      //isModefied如果文档内容已经被用户修改，则返回真否则返回假
    {
        int tips =  QMessageBox::information(this,"记事本","是否要更改保存到无标题",QMessageBox :: Yes|QMessageBox :: No|QMessageBox :: Cancel);
        if(tips == QMessageBox::Yes)
            this->saveFileSlot();
            else if(tips == QMessageBox :: No)
            qDebug()<<"您取消了按钮";
            else if(tips == QMessageBox :: Cancel)
            qDebug()<<"您取消了按钮";

    }

}


void MainWindow :: openFileSlot()//open槽
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open file",QDir::currentPath());//获取打卡文本的名字
    QFile *file = new QFile;
    file->setFileName(fileName);                 //设置文件名，没有50，52下面打开exe的时候无论做什么都回调到else,因为没有文件名，所以打开的文件失败
    bool index = file->open(QIODevice::ReadOnly);//打开文本

    if(index)                                    //判断文本是否成功打开
    {

        QTextStream in(file);                    //QTextStream 方便读写接口
        ui->textEdit->setPlainText(in.readAll());     //将文本内容全部读下来
        file->close();
        delete file;
    }
    else
    {
        //QMessageBox::information(this,"警告","文件打开失败!");
        qDebug()<<"打开失败";
        return ;
    }

}

void MainWindow :: saveFileSlot()//save槽
{
    QString saveFileName = QFileDialog::getSaveFileName(this,"Save File",QDir::currentPath());
    if(saveFileName.isEmpty())      //若(保存失败)取消保存则返回下面
    {
        qDebug()<<"保存";
    }

}

void MainWindow :: saveAsFileSlot()
{
    QString  saveAsFileName = QFileDialog :: getOpenFileName(this,"SaveAs File",QDir ::currentPath());
    if(saveAsFileName.isEmpty())
    {
        qDebug()<<"尼玛波";
        return ;
    }

    QFile *file = new QFile;                        //文件指针
    file->setFileName(saveAsFileName);              //设置文件名字

    bool index = file->open(QIODevice::WriteOnly);  //只读形式打开文件

    if(index)
    {
        QTextStream out (file);                     //将流输送到file
        out<<ui->textEdit->toPlainText();           //将全部文本取出，另存为其他
        file->close();
        delete file;
    }
    else
    {
        QMessageBox::information(this,"警告","SaveAs File error");
        return ;
    }
}


void MainWindow :: prinfFileSlot()
{




}

void MainWindow :: fontFileSlot()
{
    bool index;
         QFont font = QFontDialog::getFont(&index, QFont(), this);//获取字体，QFont()内可以不带内容也可以调用到font对话框
         if (index) {
             //ui->textEdit->setText(font.key());                                       //设置文本关键字
             ui->textEdit->setFont(font);                                               //把字体类型颜色显示到文本上
         }
}

void MainWindow :: ExitFileSlot()
{
    if(ui->textEdit->document()->isModified())      //isModefied如果文档内容已经被用户修改，则返回真否则返回假
    {
        int tips =  QMessageBox::information(this,"记事本","是否要更改保存到无标题",QMessageBox :: Yes|QMessageBox :: No|QMessageBox :: Cancel);
        if(tips == QMessageBox::Yes)
            this->saveFileSlot();
            else if(tips == QMessageBox :: No)
            qDebug()<<"您取消了按钮";
            else if(tips == QMessageBox :: Cancel)
            qDebug()<<"您什么也不做";

    }

    this->close();
}



void MainWindow :: ColorFileSlot()
{
    QColor color = QColorDialog::getColor(Qt::black, this);     //获取字体颜色,默认颜色black

         if (color.isValid()) {                                 //判断当前颜色可以用

             //这段代码是 #include <QPlainTextEdit>下实现的
             /*QPalette p2;
             p2.setColor(QPalette::Text,QColor(Qt::color0));
             ui->textEdit->setPalette(p2);
             ui->textEdit->setColor(color);*/


             ui->textEdit->setTextColor(color);                    //设置文本颜色 使用于text(不可插入图片)

            /* ui->textEdit->setText(color.name());               //将颜色名字写到文本中如0xfffff

             ui->textEdit->setPalette(QPalette(color));
             //只要没有特定的调色板被设置，或者在unsetPalette()被调用之后，这个窗口部件的特定调色板就是父窗口部件的调色板或者（如果这个窗口部件是顶级窗口部件）默认的应用程序调色板。
             //可以替代定义整个新的调色板的，你也可以使用paletteBackgroundColor、paletteBackgroundPixmap和paletteForegroundColor方便的属性来只改变窗口部件的背景和前景外观。

             ui->textEdit->setAutoFillBackground(true);         //设置相同的填充背景  */
         }
         else
         {
             //QMessageBox::information(this,"信息","更改失败！");
             qDebug()<<"颜色修改失败！";
         }
}




void MainWindow :: HelpFileSlot()
{
    QString index;
    QFile file("help.txt");
    if(!file.open(QFile::ReadOnly|QFile::Text))//打开文件  使用m模式和当前指定的文件名打开文件。如果成功，返回真，否则返回假。
	{
		qDebug()<<"打开失败！";

		return;
	}
	else
	{
        QTextStream in(&file);
		
		QMessageBox box(this);
		
        box.setWindowTitle("帮助");                  //设置标题
        box.setIcon(QMessageBox::Information);      //设置图标
        box.setText("TextEditor简介：");             //设置label
        box.setStandardButtons(QMessageBox::Ok);    //设置按钮Ok
		
        box.setDetailedText(in.readAll());          //将读入的文本显示出来
		box.exec();
		return ;
    }
}



/*void MainWindow::insertImage()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Select an image"),
                                  ".", tr("Bitmap Files (*.bmp)/n"
                                    "JPEG (*.jpg *jpeg)/n"
                                    "GIF (*.gif)/n"
                                    "PNG (*.png)/n"));

    QUrl Uri ( QString ( "file://%1" ).arg ( file ) );
    QImage image = QImageReader ( file ).read();

    QTextDocument * textDocument = ui->textEdit->document();
    textDocument->addResource( QTextDocument::ImageResource, Uri, QVariant ( image ) );
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextImageFormat imageFormat;
    imageFormat.setWidth( image.width() );
    imageFormat.setHeight( image.height() );
    imageFormat.setName( Uri.toString() );
    cursor.insertImage(imageFormat);
 }*/

/*直接调用系统的！！=。=
void MainWindow :: RedoFileSlot()
{

    //QMessageBox::information(this,"tips","luky");
    //qDebug()<<"尼玛波波";  信号槽连接错误这个函数根本跑步起来#121
    ui->textEdit->clear();
}


void MainWindow :: UndoFileSlot()    //撤销
{

}

void MainWindow :: AboutAppActionSlot()    //关于
{
    QMessageBox::information(this,"记事本","入门example");
}

void MainWindow :: CutFileSlot()     //剪切
{

}

void MainWindow :: CopyFileSlot()    //复制
{

}

void MainWindow :: PasteFileSlot()   //粘贴
{

}

void MainWindow :: DeleteFileSlot()  //删除
{

}

void MainWindow :: SeletAllFileSlot()//全选
{

}
*/

/*void MainWindow :: FindFileSlot()   //查找
{

}

void MainWindow :: InsteadFileSlot() //替换
{

}*/


void MainWindow :: DatetimeFileSlot()//时间/日期
{
    QDateTime dt =  QDateTime::currentDateTime ();      //获取系统当前时间
    QString dtime = dt.toString("yyyy-M-dd hh:mm:ss");  //将系统当前时间转换为字符串类型
    ui->textEdit->append(dtime);                        //将字符串类型的时间追加到当前文本！
}


void MainWindow ::ServiceActionSlot()
{
    QDesktopServices::openUrl( QUrl("https://www.baidu.com/"));
}

void MainWindow :: aboutSoftwareSlot()
{
    about *dialog = new about;                          //创建子对话框的对象(可以对子对话框进行操作)
    dialog->show();                                     //显示非模态对话框  下面还会用到模态对话框
}

void MainWindow ::inserPhotoSlot()  //用不了还是不会用、
{
    QTextImageFormat format;        //保存图片格式对象
    format.setName("cat.png");      //
   // ui->textEdit->textCursor().insertImage(format);//插入图片
   // QTextCursor cursor;             //编辑指针标
   // cursor.insertImage(format);     //通过编辑指针标把图片格式的文件插入资源中
}


void MainWindow ::dragEnterEvent(QDragEnterEvent *event) //判断拖拽文件是不是Text.=.=.什么都可以拖进textEdit去(继承于QWidget没有继承(即函数名是其他的，文本不接受拖放))
{
    if ((event->mimeData()->hasFormat("text/uri-list"))||(event->mimeData()->hasFormat("image/uri-list")))//过滤
            event->acceptProposedAction();                                                                //接受该动作并执行
}

bool MainWindow :: readFile(const QString &fileName)     //判断这个文件是不是只读/text文件
{
    bool r = false;
    QFile  file(fileName);                               //构造一个文件名叫做fileName的QFile
    QTextStream in(&file);                               //构造一个文本流
    if(file.open(QIODevice::ReadOnly|QFile::Text))
    {
        ui->textEdit->setText(in.readAll());
        r = true;
    }
    return r;
}


void MainWindow ::dropEvent(QDropEvent *event)           //放下事件 继承QWidget(没有继承的话实现不了显示拖拽的文本！！)
{

    QList<QUrl>urls = event->mimeData()->urls();         //返回Mime的数据对象信息保存在urls地址中
    if(urls.isEmpty())                                   //如果地址是空那么返回
        return ;

    QString fileName = urls.first().toLocalFile();       //以字符串形式返回该地址的第一个路径(list不是空那么返回第一个urls)

    //qDebug()<<fileName;

    if(fileName.isEmpty())                               //如果该地址是空那么返回
        return ;

    if(readFile(fileName))
        //设置标题：显示格式，文件路径+名字.txt+Drag File
        //setWindowTitle(tr("%1 - %2").arg(fileName).arg(tr("Drag File")));       //设置标题名字
        setWindowTitle(fileName);                                                 //还是显示 路径+名字.txt
}


void MainWindow ::dragMoveEvent(QDragMoveEvent *event)//拖动事件
{
    if (event->mimeData()->hasFormat("myimage/png")) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
    } else {
        event->ignore();
    }

}

void MainWindow ::mousePressEvent(QMouseEvent *event)           //鼠标按下事件
{
    //第一步：首先获取图片
    //将鼠标指针所在位置的部件强制转换为QLabel类型
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if(!child->inherits("QLabel"))                              //child不是QLabel类型则返回
        return ;

    QPixmap pixmap = *child->pixmap();                          //获取QLabel中的图片

    //第二步：自定义MIME类型
    QByteArray itemData;                                        //创建字节数组

    QDataStream dataStream(&itemData,QIODevice::WriteOnly);     //创建数据流
    //将图片信息、位置信息输入到字节数组中去
    dataStream<<pixmap<<QPoint(event->pos()-child->pos());


    //第三步：将数据放入QMimeData中
    QMimeData *mimeData = new QMimeData;                         //创建容器对象
    mimeData->setData("myimage/png",itemData);

    //第四步：将QMimeData 数据插入QDrag
    QDrag *drag = new QDrag(this);      // 创建QDrag，它用来移动数据
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);//在移动过程中显示图片，若不设置则默认显示一个小矩形
    drag->setHotSpot(event->pos() - child->pos()); // 拖动时鼠标指针的位置不变

    // 第五步：给原图片添加阴影
    QPixmap tempPixmap = pixmap; // 使原图片添加阴影
    QPainter painter;            // 创建QPainter，用来绘制QPixmap
    painter.begin(&tempPixmap);
    // 在图片的外接矩形中添加一层透明的淡黑色形成阴影效果
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();
    child->setPixmap(tempPixmap); // 在移动图片过程中，让原图片添加一层黑色阴影

    // 第六步：执行拖放操作
    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction)
               == Qt::MoveAction)// 设置拖放可以是移动和复制操作，默认是复制操作
        child->close();         // 如果是移动操作，那么拖放完成后关闭原标签
    else {
        child->show();            // 如果是复制操作，那么拖放完成后显示标签
        child->setPixmap(pixmap); // 显示原图片，不再使用阴影
    }

}


void MainWindow::dropPhotoEvent(QDropEvent *event) // 放下事件
{
    if (event->mimeData()->hasFormat("myimage/png"))            //不理解
    {
        QByteArray itemData = event->mimeData()->data("myimage/png");
        QDataStream  dataStream(&itemData, QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint offset;
        // 使用数据流将字节数组中的数据读入到QPixmap和QPoint变量中
         dataStream >> pixmap >> offset;
        // 新建标签，为其添加图片，并根据图片大小设置标签的大小
        QLabel *newLabel = new QLabel(this);
        newLabel->setPixmap(pixmap);
        newLabel->resize(pixmap.size());
        // 让图片移动到放下的位置，不设置的话，图片会默认显示在(0,0)点即窗口左上角
        newLabel->move(event->pos() - offset);
        newLabel->show();
        newLabel->setAttribute(Qt::WA_DeleteOnClose);
        event->setDropAction(Qt::MoveAction);
        event->accept();
   } else {
        event->ignore();
   }
}
