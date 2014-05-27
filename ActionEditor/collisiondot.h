#ifndef COLLISIONDOT_H
#define COLLISIONDOT_H

#include <QLabel>
#include <QMouseEvent>
#include <QAction>
#include <QMenu>

class CollisionDot : public QLabel
{
    Q_OBJECT
private:
    QPoint previousPos;
    bool bIsTouching;
    QAction * act_removeDot;
    QAction * act_editDot;

public:
    int groupId;
    int drawOrder;
public:
    explicit CollisionDot(QWidget *parent = 0);

signals:

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

public slots:
    void clickedAtRemoveCollisionDotButton();
    void clickedAtEditCollisionDotButton();
};

#endif // COLLISIONDOT_H
