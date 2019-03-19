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
#include <QVector>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <iostream>
#include <QtMath>
const QString allFileToString(QFile &aFile)
{
    if (!aFile.open(QFile::ReadOnly | QFile::Text)) {
        std::cout << "Error opening file!" << std::endl;
        return 0;
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

int main(/*int argc, char *argv[]*/)
{
    QVector< QVector <float> > vector;
    QFile file("C:\\ppdv\\test\\Cart360.txt");
    int b = setDataToVector(allFileToString(file).split("\n"), vector);
    printVector(vector);
    QVector< QVector <int> > MaskPos;
    QVector< QVector <int> > SpirPos;
    QVector< QVector <int> > AsPos;
    QVector< QVector <int> > RodPos;
    QVector< QVector <int> > CalPat;
    QVector< QVector <float> > PSize;

    //MaskPos=std::copy(0,2,vector);

    std::cout<<b<<"\n";

    return 0;
}
