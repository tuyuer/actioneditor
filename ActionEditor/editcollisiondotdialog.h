#ifndef EDITCOLLISIONDOTDIALOG_H
#define EDITCOLLISIONDOTDIALOG_H

#include <QDialog>
#include "collisiondot.h"

namespace Ui {
class EditCollisionDotDialog;
}

class EditCollisionDotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditCollisionDotDialog(QWidget *parent = 0);
    ~EditCollisionDotDialog();

private:
    Ui::EditCollisionDotDialog *ui;
    CollisionDot * _collisionDot;

public slots:
    void clickedAtApplyButton();
public:
    void setCollisionDot(CollisionDot * csDot);
};

#endif // EDITCOLLISIONDOTDIALOG_H
