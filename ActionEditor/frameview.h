#ifndef FRAMEVIEW_H
#define FRAMEVIEW_H

#include <QWidget>
#include <QLabel>
#include "paintview.h"

class FrameView : public QWidget
{
    Q_OBJECT
public:
    explicit FrameView(QWidget *parent = 0);

protected:

signals:

public slots:

private:

public:
    QLabel * labelPreview;
    PaintView * paintView;
public:
    void setEditable(bool bEditable);
    void resetCollisionDots();
    void reload();
};

#endif // FRAMEVIEW_H
