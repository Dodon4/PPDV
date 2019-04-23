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
#include <QtAlgorithms>
#include<QDebug>
const QString allFileToString(QFile &aFile)//считывание файла
{
    if (!aFile.open(QFile::ReadOnly | QFile::Text)) {
        std::cout << "Error opening file!" << std::endl;
        return nullptr;
    }
    QTextStream in(&aFile);
    return in.readAll();
}
size_t rows(QStringList aStringList){//получить количество строк
    int x = aStringList.size();
    return x;
}
size_t col(QStringList aStringList){//получить количество столбцов
    int y = aStringList.at((rows(aStringList))/12).count(" ");
    return y;
}
void setDataToVector(QStringList aStringList,//преоброзование считанной информации в значения
                     QVector< QVector <int> > &MaskPos,QVector< QVector <int> > &SpirPos,QVector< QVector <int> > &AsPos
                     ,QVector< QVector <int> > &RodPos,QVector< QVector <int> > &CalPat,QVector< QVector <float> > &PSize)
{
    int k=0;
    int x = rows(aStringList);
    for (int i = 0; i < x; i+=x/6)
        {
              aStringList.removeAt(i-k);
              k++;
        }

    int y = col(aStringList);
        x -= k;
    if((x % 12) != 0)
         y++;

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
void remove(QStringList &aStringList){
    int x = rows(aStringList);
    int k=0;
    for (int i = 0; i < x; i+=x/6)
        //if(aStringList.at(i-k).front() == "-")
        {
              aStringList.removeAt(i-k);
              k++;
        }
}
//Cell setDataToVector(QStringList aStringList,int i,int j)//преоброзование считанной информации в значения

//{
//    int step=rows(aStringList)/6;
//    int y=col(aStringList);
////    QString str=aStringList.at(i);
////    std::cout<<str.split(" ").at(j).toInt();
//Cell cells=Cell(aStringList.at(i).split(" ").at(j).toInt(),aStringList.at(i+step).split(" ").at(j).toInt(),
//                aStringList.at(i+2*step).split(" ").at(j).toInt(),aStringList.at(i+3*step).split(" ").at(j).toInt(),
//               aStringList.at(i+4*step).split(" ").at(j).toInt(),aStringList.at(i+5*step).split(" ").at(j).toFloat());
////    if (!file.open(QFile::ReadOnly | QFile::Text)) {
////        std::cout << "Error opening file!" << std::endl;
////    }
////    QTextStream in(&file);
////    QString str="";
////    str+=in.read(10);
////    std::cout<<str.split(" ").at(0).toInt();
//return cells;

//}
int nkas(QStringList aStringList){
    QString str=aStringList.at(1);
   if (str.size () > 0)
       str.resize (str.size () - 1);
   str.remove(0, 8);
   return str.toInt();
}
size_t rings (int r){
    size_t rings=(1 + sqrt(1 + 4 * (r - 1) / 3)) / 2;
    return rings - 1;
}
void getColors(QStringList aStringList, QVector<QVector <int>> & colors){
    int x = rows(aStringList)-1;
    for (int i =  0 ; i < x; ++i) {
        QVector<int> temp_vector;
        for (int j = 0; j < 4; ++j) {
            temp_vector.push_back(aStringList.at(i).split(";").at(j).toInt());
        }
        colors.push_back(temp_vector);
    }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   QFile file("C:\\ppdv\\dataPhenix\\Cart.txt");
   QFile file1("C:\\ppdv\\dataPhenix\\var");
   QFile file2("C:\\ppdv\\dataPhenix\\colortype");
    QStringList aStringList=allFileToString(file).split("\n");
    QStringList aStringList1=allFileToString(file1).split("\n");
    QStringList aStringList2=allFileToString(file2).split("\n");
    size_t x = (rows(aStringList)-6)/6;
    size_t y = col(aStringList);
    size_t k=x*(y+1);
    QVector<QVector <int>> colors;
    QVector< QVector <int> > MaskPos;
    QVector< QVector <int> > SpirPos;
    QVector< QVector <int> > AsPos;
    QVector< QVector <int> > RodPos;
    QVector< QVector <int> > CalPat;
    QVector< QVector <float> > PSize;
    getColors(aStringList2,colors);
    //std::cout<<colors[0].size();
//printVector(colors);
    setDataToVector(aStringList, MaskPos,SpirPos,AsPos,RodPos,CalPat,PSize);//засовываем считанную информацию по соответсвующим векторам
    Cell *cells= new Cell[k];
//    Cell cell;
    int kk=1;

    for(size_t n = 0; n <= rings(nkas(aStringList1)); n++){
    size_t j=x/2+n;
    size_t i=y/2;
    if(n==0){
        //cell=setDataToVector(aStringList,i,j);
        cells[0]=Cell(MaskPos[i][j],SpirPos[i][j],AsPos[i][j],RodPos[i][j],CalPat[i][j],PSize[i][j]);
        //cell.GetPar();
    }
    for(size_t el = 0; el < 6 * n; el++){
       // cell=setDataToVector(aStringList,i,j);
        cells[kk]=Cell(MaskPos[i][j],SpirPos[i][j],AsPos[i][j],RodPos[i][j],CalPat[i][j],PSize[i][j]);
       // cell.GetPar();
        if(el<n)
            i--;
        if(el>=n && el<2*n)
            j--;
        if(el>=2*n && el<3*n){
            i++;
            j--;
        }
        if(el>=3*n && el<4*n){
            i++;
            j++;
        }
        if(el>=4*n && el<5*n)
            j++;
        if(el>=5*n)
            i--;
        kk++;
        }
    }
//    for(int i=0;i<kk;i++)
//        cells[i].GetPar();
    QGraphicsView gv;//вывод отрисовки
    QGraphicsScene gs;
    Draw* gs1=new Draw(rings(nkas(aStringList1)),colors,cells);
    gs.addItem(gs1);
    gv.setScene(&gs);
    gv.show();
    return a.exec();
}
