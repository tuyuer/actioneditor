#include "listwidget.h"
#include <QCursor>
#include <QMenu>
#include "newactiondialog.h"
#include "mainwindow.h"
#include <QFileDialog>
#include <QMouseEvent>
#include <QApplication>
#include <QMessageBox>

ListWidget::ListWidget(QWidget *parent) :
    QListWidget(parent)
{
    this->createActions();
    widgetType = kListWidgetActions;
}

void ListWidget::createActions(){

    actNew = new QAction("创建动作", this);
    actNew->setStatusTip("创建一个新动作");
    connect(actNew, SIGNAL(triggered()), this, SLOT(clickedAtNewAction()));

    actLoadFrames = new QAction("加载资源", this);
    actLoadFrames->setStatusTip("加载角色用到的所有资源");
    connect(actLoadFrames, SIGNAL(triggered()), this, SLOT(loadCharactorResource()));

    actRemoveCharactorImage = new QAction("删除图片", this);
    actRemoveCharactorImage->setStatusTip("删除此张图片");
    connect(actRemoveCharactorImage, SIGNAL(triggered()), this, SLOT(removeCharactorImage()));

    actAddCharactorImageToFrameList = new QAction("添加图片到帧序列", this);
    actAddCharactorImageToFrameList->setStatusTip("添加角色图片到帧序列");
    connect(actAddCharactorImageToFrameList, SIGNAL(triggered()), this, SLOT(addCharactorImageToFrameList()));

    actClearAllFrames = new QAction("删除所有帧", this);
    actClearAllFrames->setStatusTip("删除当前动作的所有帧");
    connect(actClearAllFrames, SIGNAL(triggered()), this, SLOT(clearAllFrames()));

    actRemoveFrameImage = new QAction("删除当前帧", this);
    actRemoveFrameImage->setStatusTip("删除当前帧");
    connect(actRemoveFrameImage, SIGNAL(triggered()), this, SLOT(clearSelectedFrame()));
}

void ListWidget::contextMenuEvent(QContextMenuEvent *event) //右键菜单项编辑
{
    QCursor cur=this->cursor();
    QMenu *menu=new QMenu(this);

    switch (widgetType) {
    case kListWidgetActions:{
        if(this->itemAt(mapFromGlobal(cur.pos())) != NULL)
        {
           menu->addAction(new QAction("删除动作", this));
        }else{
           menu->addAction(actNew);
        }
    }
        break;
    case kListWidgetActionFrames:{
        if(this->itemAt(mapFromGlobal(cur.pos())) != NULL)
        {
           charactorImageItemSelected = this->itemAt(mapFromGlobal(cur.pos()));
           menu->addAction(actRemoveCharactorImage);
           menu->addAction(actAddCharactorImageToFrameList);
        }else{
           menu->addAction(actLoadFrames);
        }
    }
        break;
    case kListWidgetActionCurrentActionFrameList:{
        if(this->itemAt(mapFromGlobal(cur.pos())) != NULL)
        {
           menu->addAction(actRemoveFrameImage);
        }else{
           menu->addAction(actClearAllFrames);
        }
    }
        break;
    default:
        break;
    }

    menu->exec(cur.pos()); //关联到光标
}

void ListWidget::clickedAtNewAction(){
    NewActionDialog * dialog = new NewActionDialog(MainWindow::getInstance());
    dialog->setModal(true);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void ListWidget::loadCharactorResource(){
    QFileDialog* fd = new QFileDialog(MainWindow::getInstance());//创建对话框
    fd->resize(240,320);    //设置显示的大小
    fd->setFileMode( QFileDialog::ExistingFiles);
    fd->show();

    fd->setViewMode(QFileDialog::List);  //设置浏览模式，有 列表（list） 模式和 详细信息（detail）两种方式
    if ( fd->exec() == QDialog::Accepted )   //如果成功的执行
    {
        QStringList slist=fd->selectedFiles();
        MainWindow::getInstance()->loadCharactorFrames(slist);
    }
    else
        fd->close();
}

void ListWidget::removeCharactorImage(){
    QList<QListWidgetItem*> selectedItems = this->selectedItems();

    for (int i = 0; i < selectedItems.size() ; i++) {
        this->takeItem(this->row(selectedItems.at(i)));
    }
}

void ListWidget::addCharactorImageToFrameList(){
    if (MainWindow::getInstance()->currentAction == NULL) {
        QMessageBox::information(NULL, "当前动作为空", "请先创建一个动作", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    QList<QListWidgetItem*> selectedItems = this->selectedItems();

    for (int i = 0; i < selectedItems.size() ; i++) {
        QString filePath = selectedItems.at(i)->data(101).toString();
        MainWindow::getInstance()->addCharactorImageToFrameList(filePath);
    }
}

void ListWidget::clearAllFrames(){

}

void ListWidget::clearSelectedFrame(){

}

QList<QListWidgetItem*> ListWidget::allItems(){
    QList<QListWidgetItem*> listRet;
    for (int i = 0; i < this->count(); i++) {
        listRet.push_back(this->item(i));
    }
    return listRet;
}



