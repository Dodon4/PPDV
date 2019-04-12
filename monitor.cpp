#include "monitor.h"
#include "mainwindow.cpp"

QSize Monitor::min() const
{
    return m_min;
}

QSize Monitor::max() const
{
    return m_max;
}

QPixmap Monitor::prev() const
{
    return m_prev;
}


void Monitor::setPrev(QPixmap prev)
{
    m_prev = prev;
}

Monitor::Monitor(QWidget *parent): QFrame(parent)
{
    m_size=QSize(6,5);
    m_min=QSize(2,2);
    m_max=QSize(8,8);
}

QSize Monitor::cellSize() const
{
    int w =width();
    int h = height();
    int mw = max().width();
    int mh = max().height();
    int extent =qMin(w/mw,h/mh);
    return QSize(extent,extent).expandedTo(QApplication::globalStrut()).expandedTo(QSize(4,4));
}

QPoint Monitor::cellAt(const QPoint &mouse_point) const
{
    QSize cs=cellSize();
    int x = mouse_point.x()/cs.width()+1;
    int y = mouse_point.y()/cs.height()+1;
    return QPoint(x,y);
}

void Monitor::renderPreview(QPainter *painter)
{
 QSize cell_size = cellSize();
 if(!m_prev.isNull()){
     QSize sz(cell_size.width()*Value().width(),cell_size.height()*Value().height());
     painter->drawPixmap(0,0,m_prev.scaled(sz));
 }else{
     painter->setBrush(QBrush(Qt::gray));
     painter->drawRect(0,0,cell_size.width()*Value().width(),cell_size.height()*Value().height());
 }

}
void Monitor::renderGrid(QPainter *painter)
{
   QSize cell_size = cellSize();
   painter->setBrush(Qt::NoBrush);
   for(int x=0;x<m_max.width();x++)
       for(int y=0;y<m_max.height();y++){
           painter->drawRect(x*cell_size.width(),y*cell_size.height(),cell_size.width(),cell_size.height());
       }
}

void Monitor::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    renderPreview(&painter);
    renderGrid(&painter);
}

QSize Monitor::SizeHint() const
{
    return QSize(300,300);
}

void Monitor::mousePressEvent(QMouseEvent *event)
{
    QPoint mp = event->pos();
    QPoint cell = cellAt(mp);
    if(cell.x()>=min().width() && cell.x()<=max().width() &&
        cell.y()>=min().height() && cell.y()<=max().height())
        setValue(QSize(cell.x(),cell.y()));
}

void Monitor::mouseMoveEvent(QMouseEvent *event)
{
    QPoint mp = event->pos();
    QPoint cell = cellAt(mp);
    if(cell.x()>=min().width() && cell.x()<=max().width() &&
        cell.y()>=min().height() && cell.y()<=max().height())
        setValue(QSize(cell.x(),cell.y()));
}

QSize Monitor::Value() const
{
    return m_size;
}

void Monitor::setValue(QSize value)
{
    if(value == m_size)
        return;
    m_size=value;
    if (value.height()>m_max.height() ||
        value.width()>m_max.width() ||
        value.height()<m_min.height() ||
        value.width()<m_min.width())
        return;
    update();
}

void Monitor::setMin(QSize min)
{
    m_min=min;
}

void Monitor::setMax(QSize max)
{
   m_max=max;
}
