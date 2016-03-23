#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

        //��ȡϵͳ���룬��������ĵ�ʱ�򲻻����룡���ǵð���ͷ�ļ�#include <QTextCodec>������ֵ����Ķ����������ˣ���
        QTextCodec *codec = QTextCodec::codecForName("System");              //��ȡϵͳ����
        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForCStrings(codec);


        //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

        QTextCodec::setCodecForTr(codec);

        this->setWindowTitle("�ı��ĵ�.txt");//���ñ���

        //�����ź������Ӳ�   this��ʾ��ǰ����͵�ַ
        QObject::connect(ui->NewAction,SIGNAL(triggered()),this,SLOT(newFileSlot()));       //�½�
        QObject::connect(ui->OpenAction,SIGNAL(triggered()),this,SLOT(openFileSlot()));     //��
        QObject::connect(ui->SaveAction,SIGNAL(triggered()),this,SLOT(saveFileSlot()));     //����
        QObject::connect(ui->SaveAsAction,SIGNAL(triggered()),this,SLOT(saveAsFileSlot())); //���
        QObject::connect(ui->PrintfAction,SIGNAL(triggered()),this,SLOT(prinfFileSlot()));  //��ӡ
        QObject::connect(ui->ExitAction,SIGNAL(triggered()),this,SLOT(ExitFileSlot()));     //�˳�

        QObject ::connect(ui->UndoAction,SIGNAL(triggered()),ui->textEdit,SLOT(undo()));    //�༭
        QObject ::connect(ui->fontAction,SIGNAL(triggered()),this,SLOT(fontFileSlot()));    //����
        QObject ::connect(ui->ColorAction,SIGNAL(triggered()),this,SLOT(ColorFileSlot()));  //��ɫ

        QObject ::connect(ui->RedoAction,SIGNAL(triggered()),ui->textEdit,SLOT(redo()));    //����

        QObject ::connect(ui->AboutAction,SIGNAL(triggered()),qApp,SLOT(aboutQt()));        //���� qApp�Ƕ��ص�ȫ��Ӧ�ö���  �൱��ָ���qcoreapplication����
        QObject ::connect(ui->HelpAction,SIGNAL(triggered()),this,SLOT(HelpFileSlot()));    //����

        QObject ::connect(ui->CutAction,SIGNAL(triggered()),ui->textEdit,SLOT(cut()));                    //����
        QObject ::connect(ui->CopyAction,SIGNAL(triggered()),ui->textEdit,SLOT(copy()));                  //����
        QObject ::connect(ui->PasteAction,SIGNAL(triggered()),ui->textEdit,SLOT(paste()));                //ճ��
        //QObject ::connect(ui->DeleteAction,SIGNAL(triggered()),ui->textEdit,SLOT(DeletFileSlot()));     //ɾ��
        //QObject ::connect(ui->FindAction,SIGNAL(triggered()),ui->textEdit,SLOT(FindFileSlot()));        //����
        //QObject ::connect(ui->InsteadAction,SIGNAL(triggered()),ui->textEdit,SLOT(InsteadFileSlot()));  //�滻
        QObject ::connect(ui->SelectAllAction,SIGNAL(triggered()),ui->textEdit,SLOT(selectAll()));        //ȫѡ
        QObject ::connect(ui->DatetimeAction,SIGNAL(triggered()),this,SLOT(DatetimeFileSlot()));          //����/ʱ��

        QObject ::connect(ui->ServiceAction,SIGNAL(triggered()),this,SLOT(ServiceActionSlot()));          //�������


        QObject ::connect(ui->AboutAppAction,SIGNAL(triggered()),this,SLOT(aboutSoftwareSlot()));            //�ӶԻ���
}


void MainWindow :: closeEvent(QCloseEvent* event)
{

    //event->ignore();        //����˳�  ����¼��ᱻ���Բ��� �رղ����ˣ�
    //event->accept();          //����˳�  ֱ�ӽ�����  Ĭ���ǽ��յ�=��=
  
        /*int index = MessageBox::information(this,"��ʾ","��ǰ�ļ���Ϣ�Ѿ��ı䣬�Ƿ�Ҫ���浱ǰ�ļ���",tr("Yes"),tr("No"));

        if(index == tr("Yes"))
        {
            this->saveFileSlot();
        }*/
        /*

 QMessageBox msgBox;                                                                        //������Ϣ�ж���

 msgBox.setText("The document has been modified.");                                         //������Ϣ����
 msgBox.setInformativeText("Do you want to save your changes?");                            //������Ϣ����
 msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel); //���ð�ťSave Discard Cancel
 msgBox.setDefaultButton(QMessageBox::Save);                                                //����Ĭ�ϰ�ť��Save  �����س���Ĭ�ϴ���Sace
 int ret = msgBox.exec();                                                                   //�����û�ѡ��İ�ť

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
        int index = QMessageBox::information(this,"��ʾ","��ǰ�ļ���Ϣ�Ѿ��ı䣬�Ƿ�Ҫ���浱ǰ�ļ���",QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

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
        qDebug()<<"����ر�";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow :: newFileSlot()//new��
{
    if(ui->textEdit->document()->isModified())      //isModefied����ĵ������Ѿ����û��޸ģ��򷵻�����򷵻ؼ�
    {
        int tips =  QMessageBox::information(this,"���±�","�Ƿ�Ҫ���ı��浽�ޱ���",QMessageBox :: Yes|QMessageBox :: No|QMessageBox :: Cancel);
        if(tips == QMessageBox::Yes)
            this->saveFileSlot();
            else if(tips == QMessageBox :: No)
            qDebug()<<"��ȡ���˰�ť";
            else if(tips == QMessageBox :: Cancel)
            qDebug()<<"��ȡ���˰�ť";

    }

}


void MainWindow :: openFileSlot()//open��
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open file",QDir::currentPath());//��ȡ���ı�������
    QFile *file = new QFile;
    file->setFileName(fileName);                 //�����ļ�����û��50��52�����exe��ʱ��������ʲô���ص���else,��Ϊû���ļ��������Դ򿪵��ļ�ʧ��
    bool index = file->open(QIODevice::ReadOnly);//���ı�

    if(index)                                    //�ж��ı��Ƿ�ɹ���
    {

        QTextStream in(file);                    //QTextStream �����д�ӿ�
        ui->textEdit->setPlainText(in.readAll());     //���ı�����ȫ��������
        file->close();
        delete file;
    }
    else
    {
        //QMessageBox::information(this,"����","�ļ���ʧ��!");
        qDebug()<<"��ʧ��";
        return ;
    }

}

void MainWindow :: saveFileSlot()//save��
{
    QString saveFileName = QFileDialog::getSaveFileName(this,"Save File",QDir::currentPath());
    if(saveFileName.isEmpty())      //��(����ʧ��)ȡ�������򷵻�����
    {
        qDebug()<<"����";
    }

}

void MainWindow :: saveAsFileSlot()
{
    QString  saveAsFileName = QFileDialog :: getOpenFileName(this,"SaveAs File",QDir ::currentPath());
    if(saveAsFileName.isEmpty())
    {
        qDebug()<<"���겨";
        return ;
    }

    QFile *file = new QFile;                        //�ļ�ָ��
    file->setFileName(saveAsFileName);              //�����ļ�����

    bool index = file->open(QIODevice::WriteOnly);  //ֻ����ʽ���ļ�

    if(index)
    {
        QTextStream out (file);                     //�������͵�file
        out<<ui->textEdit->toPlainText();           //��ȫ���ı�ȡ�������Ϊ����
        file->close();
        delete file;
    }
    else
    {
        QMessageBox::information(this,"����","SaveAs File error");
        return ;
    }
}


void MainWindow :: prinfFileSlot()
{




}

void MainWindow :: fontFileSlot()
{
    bool index;
         QFont font = QFontDialog::getFont(&index, QFont(), this);//��ȡ���壬QFont()�ڿ��Բ�������Ҳ���Ե��õ�font�Ի���
         if (index) {
             //ui->textEdit->setText(font.key());                                       //�����ı��ؼ���
             ui->textEdit->setFont(font);                                               //������������ɫ��ʾ���ı���
         }
}

void MainWindow :: ExitFileSlot()
{
    if(ui->textEdit->document()->isModified())      //isModefied����ĵ������Ѿ����û��޸ģ��򷵻�����򷵻ؼ�
    {
        int tips =  QMessageBox::information(this,"���±�","�Ƿ�Ҫ���ı��浽�ޱ���",QMessageBox :: Yes|QMessageBox :: No|QMessageBox :: Cancel);
        if(tips == QMessageBox::Yes)
            this->saveFileSlot();
            else if(tips == QMessageBox :: No)
            qDebug()<<"��ȡ���˰�ť";
            else if(tips == QMessageBox :: Cancel)
            qDebug()<<"��ʲôҲ����";

    }

    this->close();
}



void MainWindow :: ColorFileSlot()
{
    QColor color = QColorDialog::getColor(Qt::black, this);     //��ȡ������ɫ,Ĭ����ɫblack

         if (color.isValid()) {                                 //�жϵ�ǰ��ɫ������

             //��δ����� #include <QPlainTextEdit>��ʵ�ֵ�
             /*QPalette p2;
             p2.setColor(QPalette::Text,QColor(Qt::color0));
             ui->textEdit->setPalette(p2);
             ui->textEdit->setColor(color);*/


             ui->textEdit->setTextColor(color);                    //�����ı���ɫ ʹ����text(���ɲ���ͼƬ)

            /* ui->textEdit->setText(color.name());               //����ɫ����д���ı�����0xfffff

             ui->textEdit->setPalette(QPalette(color));
             //ֻҪû���ض��ĵ�ɫ�屻���ã�������unsetPalette()������֮��������ڲ������ض���ɫ����Ǹ����ڲ����ĵ�ɫ����ߣ����������ڲ����Ƕ������ڲ�����Ĭ�ϵ�Ӧ�ó����ɫ�塣
             //����������������µĵ�ɫ��ģ���Ҳ����ʹ��paletteBackgroundColor��paletteBackgroundPixmap��paletteForegroundColor�����������ֻ�ı䴰�ڲ����ı�����ǰ����ۡ�

             ui->textEdit->setAutoFillBackground(true);         //������ͬ����䱳��  */
         }
         else
         {
             //QMessageBox::information(this,"��Ϣ","����ʧ�ܣ�");
             qDebug()<<"��ɫ�޸�ʧ�ܣ�";
         }
}




void MainWindow :: HelpFileSlot()
{
    QString index;
    QFile file("help.txt");
    if(!file.open(QFile::ReadOnly|QFile::Text))//���ļ�  ʹ��mģʽ�͵�ǰָ�����ļ������ļ�������ɹ��������棬���򷵻ؼ١�
	{
		qDebug()<<"��ʧ�ܣ�";

		return;
	}
	else
	{
        QTextStream in(&file);
		
		QMessageBox box(this);
		
        box.setWindowTitle("����");                  //���ñ���
        box.setIcon(QMessageBox::Information);      //����ͼ��
        box.setText("TextEditor��飺");             //����label
        box.setStandardButtons(QMessageBox::Ok);    //���ð�ťOk
		
        box.setDetailedText(in.readAll());          //��������ı���ʾ����
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

/*ֱ�ӵ���ϵͳ�ģ���=��=
void MainWindow :: RedoFileSlot()
{

    //QMessageBox::information(this,"tips","luky");
    //qDebug()<<"���겨��";  �źŲ����Ӵ���������������ܲ�����#121
    ui->textEdit->clear();
}


void MainWindow :: UndoFileSlot()    //����
{

}

void MainWindow :: AboutAppActionSlot()    //����
{
    QMessageBox::information(this,"���±�","����example");
}

void MainWindow :: CutFileSlot()     //����
{

}

void MainWindow :: CopyFileSlot()    //����
{

}

void MainWindow :: PasteFileSlot()   //ճ��
{

}

void MainWindow :: DeleteFileSlot()  //ɾ��
{

}

void MainWindow :: SeletAllFileSlot()//ȫѡ
{

}
*/

/*void MainWindow :: FindFileSlot()   //����
{

}

void MainWindow :: InsteadFileSlot() //�滻
{

}*/


void MainWindow :: DatetimeFileSlot()//ʱ��/����
{
    QDateTime dt =  QDateTime::currentDateTime ();      //��ȡϵͳ��ǰʱ��
    QString dtime = dt.toString("yyyy-M-dd hh:mm:ss");  //��ϵͳ��ǰʱ��ת��Ϊ�ַ�������
    ui->textEdit->append(dtime);                        //���ַ������͵�ʱ��׷�ӵ���ǰ�ı���
}


void MainWindow ::ServiceActionSlot()
{
    QDesktopServices::openUrl( QUrl("https://www.baidu.com/"));
}

void MainWindow :: aboutSoftwareSlot()
{
    about *dialog = new about;                          //�����ӶԻ���Ķ���(���Զ��ӶԻ�����в���)
    dialog->show();                                     //��ʾ��ģ̬�Ի���  ���滹���õ�ģ̬�Ի���
}

void MainWindow ::inserPhotoSlot()  //�ò��˻��ǲ����á�
{
    QTextImageFormat format;        //����ͼƬ��ʽ����
    format.setName("cat.png");      //
   // ui->textEdit->textCursor().insertImage(format);//����ͼƬ
   // QTextCursor cursor;             //�༭ָ���
   // cursor.insertImage(format);     //ͨ���༭ָ����ͼƬ��ʽ���ļ�������Դ��
}


void MainWindow ::dragEnterEvent(QDragEnterEvent *event) //�ж���ק�ļ��ǲ���Text.=.=.ʲô�������Ͻ�textEditȥ(�̳���QWidgetû�м̳�(���������������ģ��ı��������Ϸ�))
{
    if ((event->mimeData()->hasFormat("text/uri-list"))||(event->mimeData()->hasFormat("image/uri-list")))//����
            event->acceptProposedAction();                                                                //���ܸö�����ִ��
}

bool MainWindow :: readFile(const QString &fileName)     //�ж�����ļ��ǲ���ֻ��/text�ļ�
{
    bool r = false;
    QFile  file(fileName);                               //����һ���ļ�������fileName��QFile
    QTextStream in(&file);                               //����һ���ı���
    if(file.open(QIODevice::ReadOnly|QFile::Text))
    {
        ui->textEdit->setText(in.readAll());
        r = true;
    }
    return r;
}


void MainWindow ::dropEvent(QDropEvent *event)           //�����¼� �̳�QWidget(û�м̳еĻ�ʵ�ֲ�����ʾ��ק���ı�����)
{

    QList<QUrl>urls = event->mimeData()->urls();         //����Mime�����ݶ�����Ϣ������urls��ַ��
    if(urls.isEmpty())                                   //�����ַ�ǿ���ô����
        return ;

    QString fileName = urls.first().toLocalFile();       //���ַ�����ʽ���ظõ�ַ�ĵ�һ��·��(list���ǿ���ô���ص�һ��urls)

    //qDebug()<<fileName;

    if(fileName.isEmpty())                               //����õ�ַ�ǿ���ô����
        return ;

    if(readFile(fileName))
        //���ñ��⣺��ʾ��ʽ���ļ�·��+����.txt+Drag File
        //setWindowTitle(tr("%1 - %2").arg(fileName).arg(tr("Drag File")));       //���ñ�������
        setWindowTitle(fileName);                                                 //������ʾ ·��+����.txt
}


void MainWindow ::dragMoveEvent(QDragMoveEvent *event)//�϶��¼�
{
    if (event->mimeData()->hasFormat("myimage/png")) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
    } else {
        event->ignore();
    }

}

void MainWindow ::mousePressEvent(QMouseEvent *event)           //��갴���¼�
{
    //��һ�������Ȼ�ȡͼƬ
    //�����ָ������λ�õĲ���ǿ��ת��ΪQLabel����
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if(!child->inherits("QLabel"))                              //child����QLabel�����򷵻�
        return ;

    QPixmap pixmap = *child->pixmap();                          //��ȡQLabel�е�ͼƬ

    //�ڶ������Զ���MIME����
    QByteArray itemData;                                        //�����ֽ�����

    QDataStream dataStream(&itemData,QIODevice::WriteOnly);     //����������
    //��ͼƬ��Ϣ��λ����Ϣ���뵽�ֽ�������ȥ
    dataStream<<pixmap<<QPoint(event->pos()-child->pos());


    //�������������ݷ���QMimeData��
    QMimeData *mimeData = new QMimeData;                         //������������
    mimeData->setData("myimage/png",itemData);

    //���Ĳ�����QMimeData ���ݲ���QDrag
    QDrag *drag = new QDrag(this);      // ����QDrag���������ƶ�����
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);//���ƶ���������ʾͼƬ������������Ĭ����ʾһ��С����
    drag->setHotSpot(event->pos() - child->pos()); // �϶�ʱ���ָ���λ�ò���

    // ���岽����ԭͼƬ�����Ӱ
    QPixmap tempPixmap = pixmap; // ʹԭͼƬ�����Ӱ
    QPainter painter;            // ����QPainter����������QPixmap
    painter.begin(&tempPixmap);
    // ��ͼƬ����Ӿ��������һ��͸���ĵ���ɫ�γ���ӰЧ��
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();
    child->setPixmap(tempPixmap); // ���ƶ�ͼƬ�����У���ԭͼƬ���һ���ɫ��Ӱ

    // ��������ִ���ϷŲ���
    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction)
               == Qt::MoveAction)// �����Ϸſ������ƶ��͸��Ʋ�����Ĭ���Ǹ��Ʋ���
        child->close();         // ������ƶ���������ô�Ϸ���ɺ�ر�ԭ��ǩ
    else {
        child->show();            // ����Ǹ��Ʋ�������ô�Ϸ���ɺ���ʾ��ǩ
        child->setPixmap(pixmap); // ��ʾԭͼƬ������ʹ����Ӱ
    }

}


void MainWindow::dropPhotoEvent(QDropEvent *event) // �����¼�
{
    if (event->mimeData()->hasFormat("myimage/png"))            //�����
    {
        QByteArray itemData = event->mimeData()->data("myimage/png");
        QDataStream  dataStream(&itemData, QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint offset;
        // ʹ�����������ֽ������е����ݶ��뵽QPixmap��QPoint������
         dataStream >> pixmap >> offset;
        // �½���ǩ��Ϊ�����ͼƬ��������ͼƬ��С���ñ�ǩ�Ĵ�С
        QLabel *newLabel = new QLabel(this);
        newLabel->setPixmap(pixmap);
        newLabel->resize(pixmap.size());
        // ��ͼƬ�ƶ������µ�λ�ã������õĻ���ͼƬ��Ĭ����ʾ��(0,0)�㼴�������Ͻ�
        newLabel->move(event->pos() - offset);
        newLabel->show();
        newLabel->setAttribute(Qt::WA_DeleteOnClose);
        event->setDropAction(Qt::MoveAction);
        event->accept();
   } else {
        event->ignore();
   }
}
