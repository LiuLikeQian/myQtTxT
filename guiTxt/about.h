#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QDebug>
#include <QMovie>
#include <QSound>


namespace Ui {
class about;

}

class about : public QDialog
{
    Q_OBJECT
    
public:
    explicit about(QWidget *parent = 0);
    ~about();
    
private:
    Ui::about *ui;
    QMovie *movie;
    QMovie *movie2;

private slots:
    void StopSlot();
    void ContinueSlot();
};

#endif // ABOUT_H
