#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#endif // FINDDIALOG_H

#include <QWidget>
#include <QTextEdit>

#include "ui_finddialog.h"

class CFindDialog : public QWidget,
                    public Ui_finddialog
{
    Q_OBJECT

public:
    CFindDialog(QWidget *parent = 0);
    bool bolding(QTextEdit *textEdit);

private:
    QTextEdit *textEdit;
    bool direction;
    bool senstive;
    bool found;
    QWidget *parent;

private slots:
    void replace();
    void doFindLineEditChanged(const QString&);
    void doClicked();
    void doFind();
};

#endif // CFINDDIALOG_H
