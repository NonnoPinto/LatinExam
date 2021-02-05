#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QFile>
#include <QTextEdit>
#include <QFont>
#include <iostream>
#include <vector>
#include <fstream>
//#include <string>

std::vector<std::string> lvl1;
std::vector<std::string> lvl2;

/*void add(std::string& in, int linea){

    char FirstLetter = in.at(0);
        switch (FirstLetter){
        case '1':{
            lvl1.push_back(in);
        }break;
        case '2':{
            lvl2.push_back(in);
        }break;
     }
}*/

bool alreadyDone(int n, std::vector<int> vec){
    for(int i = 0; i < vec.size(); i++)
        if (n == vec[i])
            return true;

    return false;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*QFont font;
    font.setFamily(QStringLiteral("Comic Sans MS"));
    font.setPointSize(17);
    font.setBold(false);
    font.setItalic(false);
    font.setWeight(60);
    ui->textEdit->setFont(font);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Livello1_clicked()
{
    std::vector<int> already_done;
    std::string tmp = "Hello World1!!";

    if(lvl1.size()==0)
        ui->textEdit->setText("You forgot to initialize sentences!\nGo to LatinExam->Nuovo Esame");
    else{
        int num;
        do{
            srand((int)time(0));
            num = rand()*rand() % lvl1.size();
        }while (alreadyDone(num, already_done));

        already_done.push_back(num);

        tmp = "\n \n \n" + lvl1[num];

        QString qtmp = QString::fromStdString(tmp);
        ui->textEdit->setText(qtmp);}

    if (already_done.size() == lvl1.size())
        already_done.clear();
}

void MainWindow::on_Livello2_clicked()
{
    std::string tmp = "Hello World2!!";
    std::vector<int> already_done;

    if(lvl2.size()==0)
        ui->textEdit->setText("You forgot to initialize sentences!\nGo to LatinExam->Nuovo Esame");
    else{
        int num;
        do{
            srand((int)time(0));
            num = rand()*rand() % lvl2.size();
        }while (alreadyDone(num, already_done));

        already_done.push_back(num);

    tmp = "\n \n \n" + lvl2[num];
    QString qtmp = QString::fromStdString(tmp);
    ui->textEdit->setText(qtmp);}

    if (already_done.size() == lvl2.size())
        already_done.clear();

}

void MainWindow::on_actionNuovo_Esame_triggered()
{
    std::string test = "empty";

    std::fstream MyFileInput("Frasi1.txt", std::fstream::in);

    int i = 0;
    int j = 0;

    while (getline(MyFileInput, test)){
        lvl1.push_back(test);
        i++;
    }

    std::fstream  MyFileInput2("Frasi2.txt", std::fstream::in);

    while (getline(MyFileInput2, test)){
        lvl2.push_back(test);
        j++;
    }

//    test = "Ho caricato " + std::to_string(i) + " frasi di primo livello e " + std::to_string(j) + " frasi di secondo livello";
//    QString qtmp = QString::fromStdString(test);

    if(lvl1.size()==0 && lvl2.size()==0)
        ui->textEdit->setText("Non ho trovato nessuna frase!");
    else
        ui->textEdit->setText("\n \n \nPronto/a?");
}

void MainWindow::on_pushButton_clicked()
{
    ui->textEdit->setText("");
}
