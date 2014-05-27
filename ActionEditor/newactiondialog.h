#ifndef NEWACTIONDIALOG_H
#define NEWACTIONDIALOG_H

#include <QDialog>

namespace Ui {
class NewActionDialog;
}

class NewActionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NewActionDialog(QWidget *parent = 0);
    ~NewActionDialog();

private slots:
    void clickedAtCreateAction();
private:

private:
    Ui::NewActionDialog *ui;
};

#endif // NEWACTIONDIALOG_H
