#include "draw.h"
#include<QtMath>
#include<iostream>
#include<QColor>

//Draw::Draw(QVector< QVector <int> > SpirPos_):SpirPos(SpirPos_)
//{
//            size=PIECE_SIZE;
//            QPainterPath shape;
//}

Draw::Draw(size_t rings,QVector< QVector <int> > colors, Cell* cells)
    :rings(rings),colors(colors),cells(cells)//конструктор
{
        size=PIECE_SIZE;
        QPainterPath shape;

}
QColor Draw::getColor(int AsPos){
    int i = 0;
    QColor color;
while(i != 14){
    if(AsPos == colors[i][0])
       return QColor(colors[i][1],colors[i][2],colors[i][3]);
i++;

}


}
void Draw::constructShape(QPainterPath &shape,QPoint Point)//форма шестиугольника с заданным центром
{
    m_coordinates=Point;
    double stepX=size*sin(M_PI/3);
    double stepY=size*cos(M_PI/3);
    double vecX[6],vecY[6];
    vecX[0] = 0.+Point.x(); vecY[0]=size+Point.y();
    vecX[1] = -stepX+Point.x(); vecY[1]=stepY+Point.y();
    vecX[2] = -stepX+Point.x(); vecY[2]=-stepY+Point.y();
    vecX[3] = 0+Point.x(); vecY[3]=-size+Point.y();
    vecX[4] = stepX+Point.x(); vecY[4]=-stepY+Point.y();
    vecX[5] = stepX+Point.x(); vecY[5]=stepY+Point.y();
    shape.moveTo(vecX[0],vecY[0]);
    shape.lineTo(vecX[1],vecY[1]);
    shape.lineTo(vecX[2],vecY[2]);
    shape.lineTo(vecX[3],vecY[3]);
    shape.lineTo(vecX[4],vecY[4]);
    shape.lineTo(vecX[5],vecY[5]);
    shape.lineTo(vecX[0],vecY[0]);
}


void Draw::paint(QPainter * p,const QStyleOptionGraphicsItem *, QWidget *)//отрисовка шестиугольников
{
   // QColor color(0,0,255);

    double stepX=size*sin(M_PI/3);
    double stepY=size*cos(M_PI/3);
    double shiftX =0;
    double shiftY=0;
    double locX;
    double locY;
    int k=0;
    for(int j = 0; j <= rings; j++){
        if(j == 0){
            QPainterPath sh;
            constructShape(sh,QPoint(0,0));
            setPath(sh);
            p->setClipPath(path());
            QRect rect=boundingRect().toRect();
            p->fillRect(rect,getColor(cells[k].GetAsPos()));
            p->setPen(Qt::red);
            p->drawPath(path());
            }
           for(int i = 0; i < 3*j; i++){
                        //QColor color ();
                        QPainterPath sh;
                        constructShape(sh,QPoint(locX,locY));
                        setPath(sh);
                        p->setClipPath(path());
                        QRect rect=boundingRect().toRect();
                        rect=boundingRect().toRect();
                        //std::cout<<cells[k].GetAsPos()<<"\n";
                        p->fillRect(rect,getColor(cells[k].GetAsPos()));
 //                       if(i%2*j==0 && j%2==1)
 //                           p->fillRect(rect,getColor(cells[k].GetAsPos()));
//                        else
//                            p->fillRect(rect,Qt::red);
                        p->setPen(QPen(Qt::black,1,Qt::SolidLine));
                        p->drawPath(path());

                        //color ();
                        constructShape(sh,QPoint(-locX,-locY));
                        setPath(sh);
                        p->setClipPath(path());
                        rect=boundingRect().toRect();
                        p->fillRect(rect,getColor(cells[k+3*j].GetAsPos()));
//                        if(i % 2 * j == 0 && j % 2 == 0)
//                            p->fillRect(rect,Qt::black);
//                        else
//                            p->fillRect(rect,Qt::red);
                        p->setPen(QPen(Qt::black,1,Qt::SolidLine));
                        p->drawPath(path());
                        if(i >= j){
                            locX-=stepX+5*sin(M_PI/3)*0.01*size;
                            locY+=3*stepY+5*0.01*size;
                        }
                        locX-=stepX+sin(M_PI/3)*5*0.01*size;
                        locY-=3*stepY+5*0.01*size;
                        if(i >= 2 * j){

                            locX+=stepX+5*sin(M_PI/3)*0.01*size;
                            locY+=3*stepY+5*0.01*size;
                        }
                        k++;
           }
                    shiftX += 2*stepX+10*sin(M_PI/3)*0.01*size;
                    locX=shiftX;
                    locY=shiftY;
    }
}


