#ifndef DRAW_H
#define DRAW_H
#include <QPixmap>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QPainter>
#include <QWidget>
#include <QDebug>
#include<cell.h>
#define PIECE_SIZE 25

class Draw : public QGraphicsPathItem
{   // Q_OBJECT
    Q_PROPERTY(QPixmap image READ pixmap WRITE setPixmap)
    Q_PROPERTY(QPixmap coordinates READ coord WRITE setCoord)

public:
    enum Direction {North,East,South,West};
   // Draw(QVector< QVector <int> > SpirPos_);
    Draw(size_t rings,QVector< QVector <int> > colors,Cell* cells);
    void constructShape(QPainterPath& shape,QPoint Point);
    void paint(QPainter * p,const QStyleOptionGraphicsItem *,QWidget *);
    qreal size;
    int puzzle_item_count;
    QColor getColor(int AsPos);
private:
    int rings;
    QVector< QVector <int> > colors;
    Cell* cells;
public slots:

    QPixmap m_image;
    QPoint m_coordinates;

};
#endif // DRAW_H
