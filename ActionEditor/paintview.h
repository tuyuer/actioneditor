#ifndef PAINTVIEW_H
#define PAINTVIEW_H

#include <QWidget>
#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QPainter>
#include "collisiondot.h"

class PaintView : public QWidget
{
    Q_OBJECT
private:

public:
    explicit PaintView(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
signals:

public slots:
    void clickedAtAddCollisionDotButton();
private:
    bool _bIsEditing;
public:
    void setEditable(bool bEditable);
    void drawPolygons();

public:
    QPen pen;
    QBrush brush;
    QAction * act_addCollisionDot;
};

#endif // PAINTVIEW_H
