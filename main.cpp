#include "mainwindow.h"
#include <QApplication>
#include "draw.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFile>
#include <QStringList>
#include <QVector>
#include <QtMath>
#include <cell.cpp>
const QString allFileToString(QFile &aFile)//считывание файла
{
    if (!aFile.open(QFile::ReadOnly | QFile::Text)) {
        std::cout << "Error opening file!" << std::endl;
        return nullptr;
    }
    QTextStream in(&aFile);
    return in.readAll();
}
int rows(QStringList aStringList){//получить количество строк
    int x = aStringList.size() -1;
    return x;
}
int col(QStringList aStringList){//получить количество столбцов
    int y = aStringList.at((rows(aStringList)-6)/12).count(" ");
    return y;
}
void setDataToVector(QStringList aStringList,//преоброзование считанной информации в значения
                     QVector< QVector <int> > &MaskPos,QVector< QVector <int> > &SpirPos,QVector< QVector <int> > &AsPos
                     ,QVector< QVector <int> > &RodPos,QVector< QVector <int> > &CalPat,QVector< QVector <float> > &PSize)
{
    int k=0;
    int x = rows(aStringList);
    for (int i = 0; i < x; ++i) {
        if(aStringList.at(i-k).front() == "-")
        {
              aStringList.removeAt(i-k);
              k++;
        }
    }
    x -= k;
    int y = col(aStringList);
    if((x%12)!=0)
         y++;
    std::cout << x<<":"<<y<<std::endl;
    for (int i = 0; i < x/6; ++i) {
        QVector<int> temp_vector;
        for (int j = 0; j < y; ++j) {
            temp_vector.push_back(aStringList.at(i).split(" ").at(j).toInt());
        }
        MaskPos.push_back(temp_vector);
    }
    for (int i = x/6; i < x/3; ++i) {
        QVector<int> temp_vector;
        for (int j = 0; j < y; ++j) {
            temp_vector.push_back(aStringList.at(i).split(" ").at(j).toInt());
        }
        SpirPos.push_back(temp_vector);
    }
    for (int i = x / 3; i < x / 2; ++i) {
        QVector<int> temp_vector;
        for (int j = 0; j < y; ++j) {
            temp_vector.push_back(aStringList.at(i).split(" ").at(j).toInt());
        }
        AsPos.push_back(temp_vector);
    }
    for (int i = x / 2; i < 2 * x / 3; ++i) {
        QVector<int> temp_vector;
        for (int j = 0; j < y; ++j) {
            temp_vector.push_back(aStringList.at(i).split(" ").at(j).toInt());
        }
        RodPos.push_back(temp_vector);
    }
    for (int i = 2 * x / 3; i < 5 * x / 6; ++i) {
        QVector<int> temp_vector;
        for (int j = 0; j < y; ++j) {
            temp_vector.push_back(aStringList.at(i).split(" ").at(j).toInt());
        }
        CalPat.push_back(temp_vector);
    }
    for (int i = 5 * x / 6; i < x; ++i) {
        QVector<float> temp_vector;
        for (int j = 0; j < y; ++j) {
            temp_vector.push_back(aStringList.at(i).split(" ").at(j).toFloat());
        }
        PSize.push_back(temp_vector);
    }
}
void printVector(const QVector< QVector <float> > &aVector)//вывод двумерного вектора
{
    for (int i = 0; i < aVector.size(); ++i) {
        for (int j = 0; j < aVector.at(0).size(); ++j) {
            std::cout << aVector.at(i).at(j) << "\t";
        }
        std::cout << std::endl;
    }
}
void printVector(const QVector< QVector <int> > &aVector)//вывод двумерного вектора
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
    QStringList aStringList=allFileToString(file).split("\n");
    int b = (rows(aStringList)-6)/6;
    int y = col(aStringList);

    size_t k=0;
    QVector< QVector <int> > MaskPos;
    QVector< QVector <int> > SpirPos;
    QVector< QVector <int> > AsPos;
    QVector< QVector <int> > RodPos;
    QVector< QVector <int> > CalPat;
    QVector< QVector <float> > PSize;
    setDataToVector(aStringList, MaskPos,SpirPos,AsPos,RodPos,CalPat,PSize);//засовываем считанную информацию по соответсвующим векторам
    for(int i = 0; i < b; ++i)//количество элементов
        for(int j = 0; j < y; ++j)
            if(SpirPos[i][j]!=0)
                k++;


    Cell *cells= new Cell[k];
    int n =0;
    size_t kk=0;
    for(int i = 0;i < b; i++)//засовываем считанную информацию в класс ячеек
         for(int j = 0; j < y; j++){
             if(SpirPos[i][j] != 0) {
                cells[n] = Cell(MaskPos[i][j],SpirPos[i][j],AsPos[i][j],RodPos[i][j],CalPat[i][j],PSize[i][j]);
                n++;
                if(cells[n].GetCalPat() != 1)
                    kk++;
                }
            }
     Cell *CalPatCell;
    if(kk != 0){
        CalPatCell = new Cell[kk];
        for(size_t i = 0; i < k; i++)
            if(cells[i].GetCalPat() != 1)
                for(size_t j = 0; j < kk; j++){
                    int p=cells[i].GetCalPat();
                    CalPatCell[j]=Cell(p);
                }
    }
    QGraphicsView gv;//вывод отрисовки
    QGraphicsScene gs;
    Draw* gs1=new Draw();
    gs.addItem(gs1);
    gv.setScene(&gs);
    gv.show();
    return a.exec();
}
