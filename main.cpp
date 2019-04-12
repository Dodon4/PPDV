//#include "mainwindow.h"
//#include <QApplication>
//#include <QFile>
//int main(int argc, char *argv[])
//{

//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
//}
#include "mainwindow.h"
#include <QApplication>
#include "draw.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDialog>
#include <QFileDialog>
#include "monitor.h"
#include"draw.h"
#include <QGraphicsView>
#include "monitor.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include<QVector>
#include <QtMath>
#include <cell.cpp>"
const QString allFileToString(QFile &aFile)
{
    if (!aFile.open(QFile::ReadOnly | QFile::Text)) {
        std::cout << "Error opening file!" << std::endl;
        return nullptr;
    }
    QTextStream in(&aFile);
    return in.readAll();
}

int setDataToVector(QStringList aStringList,
                     QVector< QVector <float> > &aVector)
{
        int k=0;
int x = aStringList.size() -1;
    for (int i = 0; i < x; ++i) {
        if(aStringList.at(i-k).front() == "-")
        {
              aStringList.removeAt(i-k);
              k++;
        }
    }
    x -= k;
    int y = aStringList.at(x/12).count(" ");
    if((x%12)!=0)
         y++;

    std::cout << x<<":"<<y<<std::endl;
    for (int i = 0; i < x; ++i) {
        QVector<float> temp_vector;
        for (int j = 0; j < y; ++j) {
            temp_vector.push_back(aStringList.at(i).split(" ").at(j).toFloat());
        }
        aVector.push_back(temp_vector);
    }
    return x/6;
}

void printVector(const QVector< QVector <float> > &aVector)
{
    for (int i = 0; i < aVector.size(); ++i) {
        for (int j = 0; j < aVector.at(0).size(); ++j) {
            std::cout << aVector.at(i).at(j) << "\t";
        }
        std::cout << std::endl;
    }
}
void printVector(const QVector< QVector <int> > &aVector)
{
    for (int i = 0; i < aVector.size(); ++i) {
        for (int j = 0; j < aVector.at(0).size(); ++j) {
            std::cout << aVector.at(i).at(j) << "\t";
        }
        std::cout << std::endl;
    }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QVector< QVector <float> > vector;
    QFile file("C:\\ppdv\\test\\Cart360.txt");
    int b = setDataToVector(allFileToString(file).split("\n"), vector);
    size_t k=0;
   // printVector(vector);
    QVector< QVector <int> > MaskPos(b);
    QVector< QVector <int> > SpirPos(b);
    QVector< QVector <int> > AsPos(b);
    QVector< QVector <int> > RodPos(b);
    QVector< QVector <int> > CalPat(b);
    QVector< QVector <float> > PSize(b);

    for(int i = 0; i < b; ++i)
    {
        MaskPos[i].resize(3);
        for(int j = 0; j < 3; ++j)
            MaskPos[i][j] = vector[i][j];
    }
    int r=(sizeof (MaskPos[(b / 2) - 1]))/sizeof(MaskPos[0][0]);
    printVector(MaskPos);
    std::cout<<r<<"\n"<<b/2;
    for(int i = 0; i < b; ++i)
    {
        SpirPos[i].resize(3);
        for(int j = 0; j < 3; ++j)
            SpirPos[i][j] = vector[i+b][j];
    }
    for(int i = 0; i < b; ++i)
        for(int j = 0; j < 3; ++j)
            if(SpirPos[i][j]!=0)
                k++;
    std::cout<<k<<"\n";
    for(int i = 0; i < b; ++i)
    {
        AsPos[i].resize(3);
        for(int j = 0; j < 3; ++j)
            AsPos[i][j] = vector[i+2*b][j];
    }
    for(int i = 0; i < b; ++i)
    {
        RodPos[i].resize(3);
        for(int j = 0; j < 3; ++j)
            RodPos[i][j] = vector[i+3*b][j];
    }
    for(int i = 0; i < b; ++i)
    {
        CalPat[i].resize(3);
        for(int j = 0; j < 3; ++j)
            CalPat[i][j] = vector[i+4*b][j];
    }
    for(int i = 0; i < b; ++i)
    {
        PSize[i].resize(3);
        for(int j = 0; j < 3; ++j)
            PSize[i][j] = vector[i+5*b][j];
    }
    Cell *cells= new Cell[k];
    int n =0;
    size_t kk=0;
   // for(int n=0;n<k;n++)
        for(int i = 0;i < b; i++)
            for(int j = 0; j < 3; j++){
                if(SpirPos[i][j] != 0)
                {
                cells[n] = Cell(MaskPos[i][j],SpirPos[i][j],AsPos[i][j],RodPos[i][j],CalPat[i][j],PSize[i][j]);
                n++;
                if(cells[n].GetCalPat() != 1)
                    kk++;
                }
            }
     Cell *CalPatCell;
    if(kk != 0){
        CalPatCell = new Cell[kk];
        for(size_t i = 0; i < k; i++){

        if(cells[i].GetCalPat() != 1){
            for(size_t j = 0; j < kk; j++){
                int p=cells[i].GetCalPat();
                CalPatCell[j]=Cell(p);
            }
        }
        }
    }

    //QApplication a(argc, argv);
    QGraphicsView gv;
    QGraphicsScene gs;
    Draw* gs1=new Draw();
    gs.addItem(gs1);
    gv.setScene(&gs);
    gv.show();

    return a.exec();
}
