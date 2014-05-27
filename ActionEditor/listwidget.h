#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QListWidget>
#include <QtGui>
#include <QDrag>

typedef enum{
    kListWidgetActions,
    kListWidgetActionFrames,
    kListWidgetActionCurrentActionFrameList,

}ListWigetType;

class ListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit ListWidget(QWidget *parent = 0);
private:
    QPoint startPos;
    QPoint endPos;
    QMimeData *mimeData;
protected:
    void contextMenuEvent(QContextMenuEvent *event);

private:
    void createActions();
public:
    QList<QListWidgetItem*> allItems();
public:
    QAction * actNew;
    QAction * actLoadFrames;
    QAction * actRemoveCharactorImage;
    QAction * actAddCharactorImageToFrameList;
    QAction * actClearAllFrames;
    QAction * actRemoveFrameImage;
    QListWidgetItem * charactorImageItemSelected;

    ListWigetType widgetType;
public slots:
    void clickedAtNewAction();
    void loadCharactorResource();
    void removeCharactorImage();
    void addCharactorImageToFrameList();
    void clearAllFrames();
    void clearSelectedFrame();
};

#endif // LISTWIDGET_H
