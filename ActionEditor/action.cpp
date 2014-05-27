#include "action.h"

Action::Action()
{
    m_strName = "";
    m_actionId = 0;
}

void Action::addFrameItem(QListWidgetItem * frameItem){
    frameList.push_back(frameItem);
}

void Action::removeFrameItem(QListWidgetItem * frameItem){
    auto iter = std::find(frameList.begin(), frameList.end(), frameItem);
    if (iter != frameList.end())
    {
         frameList.erase(iter);
    }
}
