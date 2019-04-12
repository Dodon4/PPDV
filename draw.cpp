#include "draw.h"
#include<QPainter>
#include<QPainterPath>
#include<QPixmap>
#include <QGraphicsPixmapItem>
#include <QVariant>
#include<iostream>
#include<QtMath>
Draw::Draw(QVector< QVector <int> > SpirPos_):SpirPos(SpirPos_)
{

            //connector_position[North]=connector_position[South]=connector_position[East]=connector_position[West]=None;
            size=PIECE_SIZE;
            QPainterPath shape;
            //std::cout<<SpirPos[1][0]<<"asdasd";
            //shape.addRect(-1*size/2.,-1*size/2.,size/2,size/2);
            //shape.closeSubpath();
            //m_coordinates=QPoint(0,0);
            //m_neighbors[0]=m_neighbors[1]=m_neighbors[2]=m_neighbors[3]=0;
            //puzzle_item_count=0;
            //setPath(shape);
}

Draw::Draw()
{
        size=PIECE_SIZE;

        m_coordinates=QPoint(-1000,-1000);
    }

    QPixmap Draw::pixmap() const
    {
        return m_image;

}
void Draw::constructShape(QPainterPath &shape,QPoint Point)
{
    m_coordinates=Point;
    double stepX=size*cos(M_PI/3);
    double stepY=size*sin(M_PI/3);
    double vecX[6],vecY[6];
    vecX[0] = -stepX+Point.x(); vecY[0]=stepY+Point.y();
    vecX[1] = -size+Point.x(); vecY[1]=0.+Point.y();
    vecX[2] = -stepX+Point.x(); vecY[2]=-stepY+Point.y();
    vecX[3] = stepX+Point.x(); vecY[3]=-stepY+Point.y();
    vecX[4] = size+Point.x(); vecY[4]=0.+Point.y();
    vecX[5] = stepX+Point.x(); vecY[5]=stepY+Point.y();
    //shape.moveTo(-1000,-1000);
    shape.moveTo(vecX[0],vecY[0]);
    shape.lineTo(vecX[1],vecY[1]);
    shape.lineTo(vecX[2],vecY[2]);
    shape.lineTo(vecX[3],vecY[3]);
    shape.lineTo(vecX[4],vecY[4]);
    shape.lineTo(vecX[5],vecY[5]);
    shape.lineTo(vecX[0],vecY[0]);
}


void Draw::paint(QPainter * p, const QStyleOptionGraphicsItem * option, QWidget * widget)
{

//    bool start = false;
//    int k=0;
//    double shiftX = 2*size;
//    double shiftY=0.;
//    QPolygon polygonCentre;
//    QPolygon polygon[6];
//    p->setBrush(Qt::green);
//    for(int j = 0; j < 2; j++)
//        for(int i = 0; i < 1; i++){
//            //k++;
//            //std::cout<<k<<" "<<j<<"|";
//            shiftX -= j*(stepX-10);
//            shiftY += j*(stepY+10);
//            if(!start){
//                for(int k=0; k < 6;k++) {
//                    double locX =  vecX[k];
//                    double locY =  vecY[k];
//                }
//                    //polygonCentre << QPoint(locX,locY);
//                p->drawPolygon(polygonCentre);
//                start = true;
//             }
//             else{
//                  for(int k=0; k < 6;k++) {
//                        double locX =  shiftX+vecX[k];
//                        double locY =  shiftY+vecY[k];
//                        std::cout<<locX<<":"<<locY<<" ";
//                        polygon[2*i] << QPoint(locX,locY);
//                        polygon[2*i+1] << QPoint(-locX,-locY);
//                    }
//             }
//            std::cout<<"\n";
//                p->drawPolygon(polygon[2]);
//                p->drawPolygon(polygon[2*i+1]);
//                p->setBrush(Qt::black);
//                //shiftX += 2*(stepX-10);
//                //shiftY += 2*(stepY+10);
//         }

    double stepX=size*cos(M_PI/3);
    double stepY=size*sin(M_PI/3);
    double shiftX =0;
    double shiftY=0;
    double locX;
    double locY;
    for(int j = 0; j < 7; j++){
        if(j == 0){
            QPainterPath sh;
            constructShape(sh,QPoint(0,0));
            setPath(sh);
            p->setClipPath(path());
            QRect rect=boundingRect().toRect();
            p->fillRect(rect,Qt::black);
            p->setPen(Qt::red);
            p->drawPath(path());
//                        shiftX += size+stepX+10;
//                        shiftY += stepY+20/3;
            }
           for(int i = 0; i < 3*j; i++){

                        QPainterPath sh;
                        constructShape(sh,QPoint(locX,locY));
                        setPath(sh);
                        p->setClipPath(path());
                        QRect rect=boundingRect().toRect();
                        rect=boundingRect().toRect();
                        if(i%2*j==0 && j%2==1)
                            p->fillRect(rect,Qt::black);
                        else
                            p->fillRect(rect,Qt::green);
                        p->setPen(Qt::red);
                        p->drawPath(path());

                        constructShape(sh,QPoint(-locX,-locY));
                        setPath(sh);
                        p->setClipPath(path());
                        rect=boundingRect().toRect();
                        if(i%2*j==0 && j%2==0)
                            p->fillRect(rect,Qt::black);
                        else
                            p->fillRect(rect,Qt::green);
                        p->setPen(Qt::red);
                        p->drawPath(path());
                        if(i>=j ){


                            locX-=3*stepX+5;
                            locY+=stepY+5*sin(M_PI/3);
                        }
                        locX+=3*stepX+5;
                        locY+=stepY+5*sin(M_PI/3);
                        if(i >= 2 * j){

                            locX-=3*stepX+5;
                            locY-=stepY+5*sin(M_PI/3);
                        }


           }
                    //shiftX -= stepX+10;
                    shiftY -= 2*stepY+10*sin(M_PI/3);
                    locX=shiftX;
                    locY=shiftY;

    }

}
void Draw::setCoord(QPoint coordinates)
{
    m_coordinates = coordinates;
}
void Draw::link(Draw *p, Direction d)
{
        if(!m_neighbors[d]){
            qDebug()<<coord()<<"linked to"<<p->coord();
            m_neighbors[d]=p;
            p->itemChange(ItemPositionHasChanged,QVariant(p->pos()));
            p->link(this,(Direction)((int)d+2>3 ? (int)d-2 : (int)d+2));
        }
}
QPoint Draw::coord() const {
     return m_coordinates;
}
void Draw::setPixmap(QPixmap image)
{
        m_image=image;
        update(-1*size/2.,-1*size/2.,size,size);
}

QVariant Draw::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged && scene())
    {
        QPointF newP = value.toPointF();
        QPointF nei;
        if (m_neighbors[North])
        {
            nei = QPointF(newP.x(), newP.y() - PIECE_SIZE);
            if (m_neighbors[North]->pos() != nei) m_neighbors[North]->setPos(nei);
            //if (m_neighbours[East]->pos() != nei) m_neighbours[East]->setPos(nei);
        }
        if (m_neighbors[South])
        {
            nei = QPointF(newP.x(), newP.y() + PIECE_SIZE);
            if (m_neighbors[South]->pos() != nei) m_neighbors[South]->setPos(nei);
        }
         if (m_neighbors[East])
         {
         nei = QPointF(newP.x() + PIECE_SIZE, newP.y());
         if (m_neighbors[East]->pos() != nei) m_neighbors[East]->setPos(nei);
         }
        if (m_neighbors[West])
        {
            nei = QPointF(newP.x() - PIECE_SIZE, newP.y());
            if (m_neighbors[West]->pos() != nei) m_neighbors[West]->setPos(nei);
        }
    }
    //

    return QGraphicsItem::itemChange(change, value);
}
void Draw::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

        QSet<QPoint> neigbors;
        checkNeighbors(neigbors);
        if(neigbors.count() == puzzle_item_count)
        {
            QMessageBox::information(0,"Congratulations!","<h2>You won!</h2>");
            exit(0);
        }

        QGraphicsPathItem::mouseReleaseEvent(event);
}
void Draw::checkNeighbors(QSet<QPoint> &checked){
        if(checked.contains(coord()))
        return;
        checked.insert(coord());
        findneighbor(North);
        findneighbor(East);
        findneighbor(South);
        findneighbor(West);

        if(m_neighbors[North])
        m_neighbors[North]->checkNeighbors(checked);
        if(m_neighbors[East])
        m_neighbors[East]->checkNeighbors(checked);
        if(m_neighbors[South])
        m_neighbors[South]->checkNeighbors(checked);
        if(m_neighbors[West])
        m_neighbors[West]->checkNeighbors(checked);
}

void Draw::findneighbor(Direction d)
{
        {
            if (m_neighbors[d]) return;
            if (connector_position[d] == None) return;
            QTransform tr;
            QPoint n;
            QPoint c;
            QPointF centre = mapToScene (0,0);
            Draw *nei = 0;
            int addSize = 1;

            switch (d) {
            case North:
                c = QPoint(centre.x(), centre.y() - PIECE_SIZE - addSize);
                n = QPoint(m_coordinates.x(), m_coordinates.y() -1 );
                nei = dynamic_cast<Draw*>(scene()->itemAt(c, tr));
                break;
            case South:
                c = QPoint(centre.x(), centre.y() + PIECE_SIZE + addSize);
                n = QPoint(m_coordinates.x(), m_coordinates.y() + 1 );
                nei = dynamic_cast<Draw*>(scene()->itemAt(c, tr));
                break;
            case East:
                c = QPoint(centre.x() + PIECE_SIZE + addSize, centre.y());
                n = QPoint(m_coordinates.x() + 1, m_coordinates.y());
                nei = dynamic_cast<Draw*>(scene()->itemAt(c, tr));
                break;
            case West:
                c = QPoint(centre.x() - PIECE_SIZE - addSize, centre.y());
                n = QPoint(m_coordinates.x() - 1, m_coordinates.y());
                nei = dynamic_cast<Draw*>(scene()->itemAt(c, tr));
                break;
            }
            if (nei)
                if (nei->coord() == n) link(nei, d);

        }

}
