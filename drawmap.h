#ifndef DRAWMAP_H
#define DRAWMAP_H


#include "draw.h"
#include <QGraphicsScene>
class DrawMap : public QGraphicsScene
{
public:
     ConnectorPosition reverse(ConnectorPosition pos);
    DrawMap(){}
    ~DrawMap(){}
    void setup(QSize size,QPixmap pixmap);
};

#endif // DRAWMAP_H
