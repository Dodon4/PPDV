#ifndef MONITOR_H
#define MONITOR_H
#include <QFrame>
#include <QObject>
#include <QPixmap>
#include <QPainter>
#include <QApplication>
#include <QMouseEvent>
#include "draw.h"
class Monitor: public QFrame
{
    QSize m_size;
    QSize m_min;
    QSize m_max;

    QPixmap m_prev;
public:
    Monitor(QWidget *parent = nullptr) ;

    QSize cellSize() const;
    QPoint cellAt(const QPoint&mouse_point) const;
    void renderPreview(QPainter *painter);
    void renderGrid(QPainter *painter);

    void paintEvent(QPaintEvent *);
    QSize SizeHint() const;
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);

    QSize Value() const;
    QSize min() const;
    QSize max() const;


    QPixmap prev() const;



public slots:
    void setValue(QSize value);
    void setMin(QSize min);
    void setMax(QSize max);
    void setPrev(QPixmap prev);
};

#endif // MONITOR_H
