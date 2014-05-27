#ifndef ACTION_H
#define ACTION_H
#include <iostream>
#include <QListWidgetItem>

class Action
{
public:
    Action();
public:
    std::string m_strName;
    int m_actionId;
    std::vector<QListWidgetItem*> frameList;

public:
    void addFrameItem(QListWidgetItem * frameItem);
    void removeFrameItem(QListWidgetItem * frameItem);

};

#endif // ACTION_H
