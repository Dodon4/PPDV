#ifndef DRAW_H
#define DRAW_H
#include <QPixmap>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QPainter>
#include <QWidget>
#include <QDebug>
#define PIECE_SIZE 40

class Draw : public QGraphicsPathItem
{   // Q_OBJECT
    Q_PROPERTY(QPixmap image READ pixmap WRITE setPixmap)
    Q_PROPERTY(QPixmap coordinates READ coord WRITE setCoord)

public:
    enum Direction {North,East,South,West};
    Draw(QVector< QVector <int> > SpirPos_);
    Draw();
    void constructShape(QPainterPath& shape,QPoint Point);
    void paint(QPainter * p,QWidget * widget);
    qreal size;
    int puzzle_item_count;

private:
public slots:
    QVector< QVector <int> > SpirPos;
    QPixmap m_image;
    QPoint m_coordinates;

};
inline uint qHash (const QPoint &key,uint seed)
{
return qHash(key.x(),seed)*key.y();}
#endif // DRAW_H
