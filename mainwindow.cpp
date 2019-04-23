#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include<QTextStream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}


//    int i=1,j=0;
//            int dirJ=1,dirI=-1;
//            std::cout<<k;
//            std::cout<<1;
//           printVector(MaskPos);
//    for(int n = 0; n < k; n++){

//        j += dirJ;
//        std::cout<<i<<":"<<j<<"\n";
//        //cells[n]=Cell(MaskPos[i][j],SpirPos[i][j],AsPos[i][j],RodPos[i][j],CalPat[i][j],PSize[i][j]);
//        if(j!=0 && i!=2)
//            if(SpirPos[i][j-1]==0){
//               // std::cout<<"\nabs"<<SpirPos[i][j-1];
//                i+=dirI;
//                j-=2;
//                dirJ = -dirJ;
//            }
//        if(j % 2 == 0 && i!=0){
//            i += dirI;
//            dirJ = -dirJ;
//            dirI = -dirI;
//            j +=1;
//            if(SpirPos[i][0]==0 && j==0)
//                j +=1;
//        }
//          }
