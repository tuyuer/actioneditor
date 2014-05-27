#include "collisiondot.h"
#include "paintview.h"
#include "mainwindow.h"
#include "editcollisiondotdialog.h"

CollisionDot::CollisionDot(QWidget *parent) :
    QLabel(parent)
{
    QPixmap pixmap(QString(":/menu/collisiondot.png"));
    this->setPixmap(pixmap);
    this->resize(pixmap.width(),pixmap.height());

    act_removeDot = new QAction("移除碰撞点", this);
    act_removeDot->setStatusTip("移除此碰撞点");
    connect(act_removeDot, SIGNAL(triggered()), this, SLOT(clickedAtRemoveCollisionDotButton()));

    act_editDot = new QAction("编辑碰撞点", this);
    act_editDot->setStatusTip("编辑此碰撞点");
    connect(act_editDot, SIGNAL(triggered()), this, SLOT(clickedAtEditCollisionDotButton()));


}

void CollisionDot::mouseMoveEvent(QMouseEvent *event)
{

    if( bIsTouching ){
        QPoint moveOffset = QPoint( event->x() - previousPos.x(),event->y() -previousPos.y() );

        QRect labelGeometry = this->geometry();
        int imgWidth = labelGeometry.width();
        int imageHeight = labelGeometry.height();
        labelGeometry.setX(labelGeometry.x() + moveOffset.x());
        labelGeometry.setY(labelGeometry.y() + moveOffset.y());
        labelGeometry.setWidth(imgWidth);
        labelGeometry.setHeight(imageHeight);
        this->setGeometry(labelGeometry);
    }
}

void CollisionDot::mousePressEvent(QMouseEvent *event)
{
    bIsTouching = true;
    previousPos = QPoint(event->x(),event->y());
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->raise();
}

void CollisionDot::mouseReleaseEvent(QMouseEvent *event)
{
    bIsTouching = false;
    MainWindow::getInstance()->drawCollisionPolygons();
}

void CollisionDot::contextMenuEvent(QContextMenuEvent *event) //右键菜单项编辑
{
    QCursor cur=this->cursor();
    QMenu *menu=new QMenu(this);
    menu->addAction(act_removeDot); //添加菜单项1
    menu->addAction(act_editDot);
    menu->exec(cur.pos()); //关联到光标
}

void CollisionDot::clickedAtRemoveCollisionDotButton(){
    MainWindow::getInstance()->currentFrameInfo->removeDot(this);
    this->hide();
    delete this;
}

void CollisionDot::clickedAtEditCollisionDotButton(){
    EditCollisionDotDialog * dialog = new EditCollisionDotDialog(this);
    dialog->setModal(true);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
    dialog->setCollisionDot(this);
}
