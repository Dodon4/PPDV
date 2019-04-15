#include "drawmap.h"
#include "draw.h"
#include <QTime>
#include "monitor.h"
#include "mainwindow.h"
#include <QRandomGenerator>
ConnectorPosition DrawMap:: reverse(ConnectorPosition pos) {
switch(pos){
    case None: return None;
    case In: return Out;
    case Out: return In;
    }
        return None;
}
void DrawMap::setup(QSize size, QPixmap pixmap)
{
    const int cellsize=PIECE_SIZE;
    clear();
    qsrand(QTime::currentTime().msec());

    for(int row=0; row<size.height();++row)
    {
        for(int col=0;col<size.width();++col)
        {
        Draw *piece = new Draw();
        addItem(piece);
        piece->setFlag(QGraphicsItem::ItemIsMovable);
        piece->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
        piece->setPos(QRandomGenerator::global()->bounded(500-piece->size),QRandomGenerator::global()->bounded(500-piece->size));
        QRect rect=piece->boundingRect().toRect();
        rect.translate(0.5*cellsize+col*cellsize,0.5*cellsize+row*cellsize);
        QPixmap qim=pixmap.copy(rect);
        piece->setPixmap(qim);
        piece->setCoord(QPoint(col,row));
        piece->puzzle_item_count=size.width()*size.height();
        }

    }

}
