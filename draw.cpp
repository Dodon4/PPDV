#include "draw.h"
#include<QtMath>
Draw::Draw(QVector< QVector <int> > SpirPos_):SpirPos(SpirPos_)
{
            size=PIECE_SIZE;
            QPainterPath shape;
}

Draw::Draw()//конструктор
{
        size=PIECE_SIZE;

        m_coordinates=QPoint(-1000,-1000);
    }

void Draw::constructShape(QPainterPath &shape,QPoint Point)//форма шестиугольника с заданным центром
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
    shape.moveTo(vecX[0],vecY[0]);
    shape.lineTo(vecX[1],vecY[1]);
    shape.lineTo(vecX[2],vecY[2]);
    shape.lineTo(vecX[3],vecY[3]);
    shape.lineTo(vecX[4],vecY[4]);
    shape.lineTo(vecX[5],vecY[5]);
    shape.lineTo(vecX[0],vecY[0]);
}


void Draw::paint(QPainter * p, QWidget * widget)//отрисовка шестиугольников
{
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
                    shiftY -= 2*stepY+10*sin(M_PI/3);
                    locX=shiftX;
                    locY=shiftY;
    }
}


