#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newactiondialog.h"
#include "action.h"
#include "listwidget.h"
#include "frameinfo.h"
#include <QVariant>
#include <QMessageBox>

static MainWindow * s_sharedMainWindow = NULL;
MainWindow * MainWindow::getInstance(){
    return s_sharedMainWindow;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    s_sharedMainWindow = this;
    ui->setupUi(this);

    ui->lw_actionList->widgetType = kListWidgetActions;
    ui->lw_currentActionFrames->widgetType = kListWidgetActionFrames;
    ui->lw_currentAction->widgetType = kListWidgetActionCurrentActionFrameList;

    ui->lw_currentActionFrames->setIconSize(QSize(40,40));
    ui->lw_currentAction->setIconSize(QSize(40,40));

    //drag and drop surport
    ui->lw_currentAction->setAcceptDrops(true);
    ui->lw_currentAction->setDragDropMode(QAbstractItemView::InternalMove);
    ui->lw_currentActionFrames->setDragDropMode(QAbstractItemView::InternalMove);
    ui->lw_currentActionFrames->setSelectionMode(QAbstractItemView::ContiguousSelection);

    this->createActions();
    this->createToolBars();

    timerUpdateFrame = new QTimer(this);
    connect(timerUpdateFrame, SIGNAL(timeout()), this, SLOT(updateFrame()));

    frameIndex = 0;
    currentFrameInfo = NULL;
    currentAction = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    newAct = new QAction(QIcon(":/menu/newaction.png"), "&New", this);
    newAct->setStatusTip("创建一个新动作");
    connect(newAct, SIGNAL(triggered()), this, SLOT(clickedAtNewAction()));

    connect(ui->lw_currentAction, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(currentActionFrameChanged(QListWidgetItem*,QListWidgetItem*)));
    connect(ui->lw_actionList,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(actionListItemChanged(QListWidgetItem*,QListWidgetItem*)));
    connect(ui->sliderDelayPerUnit, SIGNAL(valueChanged(int)), this, SLOT(delayPerUnitValueChanged(int)));
    connect(ui->sliderCurrentFrame, SIGNAL(valueChanged(int)), this, SLOT(currentFrameValueChanged(int)));
    connect(ui->btnPlayState, SIGNAL(clicked()), this, SLOT(clickedAtBtnState()));
}

void MainWindow::createToolBars()
{
    ui->mainToolBar->addAction(newAct);
}

void MainWindow::clickedAtNewAction(){
    NewActionDialog * dialog = new NewActionDialog(this);
    dialog->setModal(true);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void MainWindow::currentActionFrameChanged(QListWidgetItem* currentItem,QListWidgetItem* previousItem){
    if (currentItem == NULL) {
        return;
    }

    QString filePath = currentItem->data(101).toString();

    int frameInfoId = currentItem->data(102).toInt();
    currentFrameInfo = NULL;
    for (int i = 0; i < frameInfoList.size(); i++) {
        FrameInfo * frameInfo = frameInfoList.at(i);
        if (frameInfoId == frameInfo->frameId) {
            currentFrameInfo = frameInfo;
        }
    }

    QPixmap pixMap(filePath.toUtf8().data());
    ui->widgetFrameView->labelPreview->setPixmap(pixMap);
    ui->widgetFrameView->labelPreview->setGeometry(ui->widgetFrameView->labelPreview->geometry().x(),ui->widgetFrameView->labelPreview->geometry().y(),pixMap.width(),pixMap.height());
    ui->widgetFrameView->paintView->setGeometry(ui->widgetFrameView->paintView->geometry().x(),ui->widgetFrameView->paintView->geometry().y(),pixMap.width(),pixMap.height());


    float scrollWidth = ui->scrollArea->size().width();
    float scrollHeight = ui->scrollArea->size().height();

    ui->widgetFrameView->setGeometry((scrollWidth-pixMap.width())/2,(scrollHeight-pixMap.height())/2,pixMap.width(),pixMap.height());
    ui->widgetFrameView->resetCollisionDots();
}

void MainWindow::actionSelectChanged(){
    currentFrameInfo = NULL;

    QList<QListWidgetItem*> allFrames = ui->lw_currentAction->allItems();
    for (int i = 0; i < allFrames.size(); i++) {
        QListWidgetItem * itemToRemove = allFrames.at(i);
        int rowToRemove = ui->lw_currentAction->row(itemToRemove);
        ui->lw_currentAction->takeItem(0);
    }

    for (int i = 0; i < currentAction->frameList.size(); i++) {
        QListWidgetItem * item = currentAction->frameList.at(i);
        ui->lw_currentAction->insertItem(i,item);
    }
    ui->widgetFrameView->reload();
}

void MainWindow::actionListItemChanged(QListWidgetItem* currentItem,QListWidgetItem* previousItem){
    int actionId = currentItem->data(102).toInt();
    for (int i = 0; i < actionList.size(); i++) {
        Action * actionInfo = actionList.at(i);
        if (actionId == actionInfo->m_actionId) {
            currentAction = actionInfo;
            this->actionSelectChanged();
            break;
        }
    }
    ui->lw_actionList->setCurrentItem(currentItem);
}

void MainWindow::delayPerUnitValueChanged(int newValue){
    float timeUnit = newValue*1.0/99;
    char chNewValue[10];
    sprintf(chNewValue,"%.2f",timeUnit);
    ui->labelDelayPerUnit->setText(QString(chNewValue));

    QString strStateValue = ui->btnPlayState->text();
    if (strStateValue.endsWith(QString("暂停"))) {
        timerUpdateFrame->stop();
        timerUpdateFrame->start(timeUnit*1000);
    }
}

void MainWindow::currentFrameValueChanged(int newValue){
    int newIndex = newValue*1.0/ 100 * ui->lw_currentAction->count();
    frameIndex = newIndex;
}

void MainWindow::clickedAtBtnState(){

   QString strStateValue = ui->btnPlayState->text();
   if (strStateValue.endsWith(QString("播放"))) {
       ui->btnPlayState->setText("暂停");
       timerUpdateFrame->stop();

       float delayPerUnit = atof(ui->labelDelayPerUnit->text().toUtf8().data());
       timerUpdateFrame->start(delayPerUnit*1000);
   }else{
       ui->btnPlayState->setText("播放");
       timerUpdateFrame->stop();
   }
}

void MainWindow::updateFrame(){

    if (ui->lw_currentAction->count() > 0) {
        if (frameIndex >= ui->lw_currentAction->count()) {
            frameIndex = 0;
        }
        QListWidgetItem * frameItem = ui->lw_currentAction->item(frameIndex);

        int frameInfoId = frameItem->data(102).toInt();
        currentFrameInfo = NULL;
        for (int i = 0; i < frameInfoList.size(); i++) {
            FrameInfo * frameInfo = frameInfoList.at(i);
            if (frameInfoId == frameInfo->frameId) {
                currentFrameInfo = frameInfo;
            }
        }

        QString filePath = frameItem->data(101).toString();
        QPixmap pixMap(filePath.toUtf8().data());
        ui->widgetFrameView->labelPreview->setPixmap(pixMap);
        ui->widgetFrameView->labelPreview->setGeometry(ui->widgetFrameView->labelPreview->geometry().x(),ui->widgetFrameView->labelPreview->geometry().y(),pixMap.width(),pixMap.height());
        ui->widgetFrameView->paintView->setGeometry(ui->widgetFrameView->paintView->geometry().x(),ui->widgetFrameView->paintView->geometry().y(),pixMap.width(),pixMap.height());
        float scrollWidth = ui->scrollArea->size().width();
        float scrollHeight = ui->scrollArea->size().height();

        ui->widgetFrameView->setGeometry((scrollWidth-pixMap.width())/2,(scrollHeight-pixMap.height())/2,pixMap.width(),pixMap.height());
        ui->lw_currentAction->setCurrentRow(frameIndex);


        frameIndex++;

        char chIndex[10];
        sprintf(chIndex,"%d",frameIndex);
        ui->labelCurrentFrameIndex->setText(chIndex);
        ui->sliderCurrentFrame->setValue( frameIndex*1.0/ui->lw_currentAction->count() *100 );

        ui->widgetFrameView->resetCollisionDots();
    }
}

void MainWindow::createNewAction(const char * chName){
    static int s_actionId = 1024 ;
    Action * action = new Action();
    action->m_strName = chName;
    action->m_actionId = s_actionId;
    actionList.push_back(action);


    QListWidgetItem* lstItem = new QListWidgetItem(chName,ui->lw_actionList);
    lstItem->setData(102,s_actionId);

    s_actionId++;
}

void MainWindow::loadCharactorFrames(QStringList & strList){
    for (int i = 0; i < strList.size(); i++) {
        QString filePath = strList.at(i);
        QListWidgetItem* lstItem = new QListWidgetItem(QIcon(filePath), filePath.split("/").last().toUtf8().data(),ui->lw_currentActionFrames);
        lstItem->setData(101,filePath);
    }
}

void MainWindow::addCharactorImageToFrameList(QString & filePath){

    static int s_frameId = 1024;
    QListWidgetItem* lstItem = new QListWidgetItem(QIcon(filePath), filePath.split("/").last().toUtf8().data(),ui->lw_currentAction);
    lstItem->setData(101,filePath);
    lstItem->setData(102,s_frameId);

    FrameInfo * frameInfo = new FrameInfo();
    frameInfo->frameId =s_frameId;

    frameInfoList.push_back(frameInfo);
    currentAction->frameList.push_back(lstItem);

    s_frameId++;
}

void MainWindow::editFrameCollision(bool bEditable){
    ui->widgetFrameView->setEditable(bEditable);
}

void MainWindow::drawCollisionPolygons(){
   ui->widgetFrameView->resetCollisionDots();
}
