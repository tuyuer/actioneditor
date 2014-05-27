#include "newactiondialog.h"
#include "ui_newactiondialog.h"
#include "mainwindow.h"

NewActionDialog::NewActionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewActionDialog)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(clickedAtCreateAction()));
}

NewActionDialog::~NewActionDialog()
{
    delete ui;
}

void NewActionDialog::clickedAtCreateAction(){
    QString actionName = ui->textEdit->toPlainText();
    this->close();

    MainWindow::getInstance()->createNewAction(actionName.toUtf8().data());
}
