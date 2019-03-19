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
            QString str="";
    QFile file("C:\\ppdv\\test\\Cart360.txt");
    QFile file1("C:\\ppdv\\test\\Cart3601.txt");
    QStringList lst;
    QString ar[1];
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {

//        while(!file.atEnd())
//        {
//
//        }
        //int a[];
        //str=getline;
//        file.readLine();
//        str=file.readLine();
//        lst=str.split(" ");
//        str=lst.at(1)+lst.at(2)+lst.at(3);
//        process_line();
       // str=str+file.read(2);

        file.close();
    }
    //QStringList strList;
    if ((file1.exists())&&(file1.open(QIODevice::WriteOnly)))
    {
       // str.insert(2,"Inserted string\n");
        QTextStream stream(&file1);
        foreach(QString s, str)
        {
            stream<<s;
        }
        file1.close();
    }
}


