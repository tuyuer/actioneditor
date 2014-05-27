#include "paintview.h"
#include <QAction>
#include <QMenu>
#include "collisiondot.h"
#include "mainwindow.h"

PaintView::PaintView(QWidget *parent) :
    QWidget(parent)
{
    brush = QBrush(Qt::green);
    _bIsEditing = false;

    act_addCollisionDot = new QAction("添加碰撞点", this);
    act_addCollisionDot->setStatusTip("创建一个碰撞点");
    connect(act_addCollisionDot, SIGNAL(triggered()), this, SLOT(clickedAtAddCollisionDotButton()));
}

void PaintView::clickedAtAddCollisionDotButton(){
    static int s_drawOrderIndex = 0;
    CollisionDot * csDot = new CollisionDot(this);
    csDot->show();
    csDot->groupId = 1;
    csDot->drawOrder = s_drawOrderIndex++;

    MainWindow::getInstance()->currentFrameInfo->addDot(csDot);

    QCursor cur=this->cursor();
    QPoint curPos = mapFromGlobal(cur.pos());
    csDot->setGeometry(curPos.x(),curPos.y(),10,10);

    this->drawPolygons();
}


void PaintView::paintEvent(QPaintEvent *event){
    if (MainWindow::getInstance()->currentFrameInfo == NULL) {
        return;
    }

    QPainterPath path;

    QPainter painter(this);
    painter.setBrush(brush);
    painter.setPen(palette().dark().color());

    FrameInfo * currentFrameInfo = MainWindow::getInstance()->currentFrameInfo;

    for (int groupIndex = 0; groupIndex < 11; groupIndex++) {
        std::vector<CollisionDot*> collisionDotGroup;

        for (int i = 0; i < currentFrameInfo->collisionDotList.size(); i++) {
            CollisionDot * dot = currentFrameInfo->collisionDotList.at(i);
            if (dot->groupId == groupIndex) {
                collisionDotGroup.push_back(dot);
            }
        }

        QPoint * ptPolygen =(QPoint *) malloc(sizeof(QPoint)*collisionDotGroup.size());
        for (int i = 0; i < collisionDotGroup.size(); i++) {
            CollisionDot * dot = collisionDotGroup.at(i);
            ptPolygen[i].setX(dot->pos().x()+5);
            ptPolygen[i].setY(dot->pos().y()+5);
        }

        if (groupIndex <= 5) {
            painter.setBrush(QBrush(QColor(100,0,0,100)));
        }else{
            painter.setBrush(QBrush(QColor(0,100,0,100)));
        }

        painter.save();
        painter.drawPolygon(ptPolygen,collisionDotGroup.size());
        painter.restore();
    }
}

void PaintView::drawPolygons(){
    for (int frameInfoIndex = 0; frameInfoIndex < MainWindow::getInstance()->frameInfoList.size(); frameInfoIndex++) {
        FrameInfo * frameInfo = MainWindow::getInstance()->frameInfoList.at(frameInfoIndex);
        for (int i = 0; i < frameInfo->collisionDotList.size(); i++) {
            CollisionDot * csDot = frameInfo->collisionDotList.at(i);
            csDot->setHidden(true);
        }
    }

    if (MainWindow::getInstance()->currentFrameInfo !=NULL) {
        for (int i = 0; i < MainWindow::getInstance()->currentFrameInfo->collisionDotList.size(); i++) {
            CollisionDot * csDot =  MainWindow::getInstance()->currentFrameInfo->collisionDotList.at(i);
            csDot->setHidden(false);
        }
        update();
    }
}


void PaintView::setEditable(bool bEditable){
    _bIsEditing = bEditable;
    update();
}

void PaintView::contextMenuEvent(QContextMenuEvent *event){
    if (MainWindow::getInstance()->currentFrameInfo == NULL) {
        return;
    }

    QCursor cur=this->cursor();
    QMenu *menu=new QMenu(this);
    menu->addAction(act_addCollisionDot); //添加菜单项1
    menu->exec(cur.pos()); //关联到光标
}
