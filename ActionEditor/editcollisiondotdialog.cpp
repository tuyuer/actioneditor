#include "editcollisiondotdialog.h"
#include "ui_editcollisiondotdialog.h"
#include <QIntValidator>
#include "mainwindow.h"

EditCollisionDotDialog::EditCollisionDotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditCollisionDotDialog)
{
    ui->setupUi(this);
    ui->editGroupId->setValidator(new QIntValidator(0, 10, this));
    ui->editDrawOrder->setValidator(new QIntValidator(0, 1000, this));
    ui->editDrawOrder->setEnabled(false);

    connect(ui->btnApply, SIGNAL(clicked()), this, SLOT(clickedAtApplyButton()));
}

EditCollisionDotDialog::~EditCollisionDotDialog()
{
    delete ui;
}

void EditCollisionDotDialog::clickedAtApplyButton(){
    _collisionDot->groupId = ui->editGroupId->text().toInt();
    MainWindow::getInstance()->drawCollisionPolygons();
    this->close();
}

void EditCollisionDotDialog::setCollisionDot(CollisionDot * csDot){
    _collisionDot = csDot;

    char chGroupId[20];
    sprintf(chGroupId,"%d",_collisionDot->groupId);

    char chDrawOrder[20];
    sprintf(chDrawOrder,"%d",_collisionDot->drawOrder);

    ui->editGroupId->setText(chGroupId);
    ui->editDrawOrder->setText(chDrawOrder);
}








