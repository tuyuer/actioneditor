#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "action.h"
#include <QListWidgetItem>
#include "frameinfo.h"
#include "action.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static MainWindow * getInstance();
private slots:
    void clickedAtNewAction();
    void currentActionFrameChanged(QListWidgetItem* currentItem,QListWidgetItem* previousItem);
    void actionListItemChanged(QListWidgetItem* currentItem,QListWidgetItem* previousItem);
    void delayPerUnitValueChanged(int newValue);
    void currentFrameValueChanged(int newValue);
    void clickedAtBtnState();
    void updateFrame();
private:
    void createActions();
    void createToolBars();

    void actionSelectChanged();
private:
    QTimer  *timerUpdateFrame;
    int frameIndex;
    QAction *newAct;

private:
    Ui::MainWindow *ui;
public:
    std::vector<Action*> actionList;
    std::vector<FrameInfo*> frameInfoList;

    FrameInfo * currentFrameInfo;
    Action * currentAction;
public:
    void createNewAction(const char * chName);
    void loadCharactorFrames(QStringList & strList);
    void addCharactorImageToFrameList(QString & filePath);
    void editFrameCollision(bool bEditable);

    void drawCollisionPolygons();
};

#endif // MAINWINDOW_H
