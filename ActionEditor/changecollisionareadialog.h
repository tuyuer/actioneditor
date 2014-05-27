#ifndef CHANGECOLLISIONAREADIALOG_H
#define CHANGECOLLISIONAREADIALOG_H

#include <QDialog>

namespace Ui {
class ChangeCollisionAreaDialog;
}

class ChangeCollisionAreaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeCollisionAreaDialog(QWidget *parent = 0);
    ~ChangeCollisionAreaDialog();

private:
    Ui::ChangeCollisionAreaDialog *ui;
public slots:
    void editWidthChanged(const QString & newStr);
    void editHeightChanged(const QString & newStr);
public:
    void setCollisionAreaSize(int width,int height);
public:
    QWidget * receiverWidget;
};

#endif // CHANGECOLLISIONAREADIALOG_H
