#include "frameview.h"

FrameView::FrameView(QWidget *parent) :
    QWidget(parent)
{
    labelPreview = new QLabel(this);
    paintView = new PaintView(this);
    paintView->resize(400,400);

    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(192,253,123));
    this->setPalette(palette);
}


void FrameView::setEditable(bool bEditable){
    paintView->setEditable(bEditable);
}

void FrameView::resetCollisionDots(){
    paintView->drawPolygons();
}

void FrameView::reload(){
    labelPreview->setPixmap(QPixmap());
    paintView->drawPolygons();
}
