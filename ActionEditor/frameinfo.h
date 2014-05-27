#ifndef FRAMEINFO_H
#define FRAMEINFO_H

#include <QObject>
#include "collisiondot.h"

class FrameInfo : public QObject
{
    Q_OBJECT
public:
    FrameInfo();
signals:

public slots:

public:
    int frameId;
    std::vector<CollisionDot*> collisionDotList;
public:
    void addDot(CollisionDot * dot);
    void removeDot(CollisionDot * dot);
};
#endif // FRAMEINFO_H
