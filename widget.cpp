#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QListView>
#include <QStringListModel>
#include<QTextStream>
#include <QStringList>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QPalette>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    model = new QStringListModel();

    //Widget->setStyleSheet("background-color:lightsteelblue");
    this->setStyleSheet("background-color:lightsteelblue");
    ui->pButton->setStyleSheet("background-color:aquamarine");
    ui->kButton->setStyleSheet("background-color:aquamarine");
    ui->rButton->setStyleSheet("background-color:aquamarine");
    ui->sButton->setStyleSheet("background-color:aquamarine");
    ui->startButton->setStyleSheet("background-color:fuchsia");
    ui->displayRemWordsButton->setStyleSheet("background-color:goldenrod");
    ui->numWordsRemainingLabel->setStyleSheet("background-color:lightgreen;padding:5px");
    ui->bestWordLabel->setStyleSheet("background-color:lightgreen;padding:5px");
    ui->letterLineEdit->setStyleSheet("background-color:ghostwhite");
    ui->placementSpinBox->setStyleSheet("background-color:ghostwhite");
    ui->remainingWordsListView->setStyleSheet("background-color:ghostwhite");



}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_startButton_clicked()
{

    QFile words("D:/Qt_proj/wordle/list_of_words/wordlist.txt");
    if(!words.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0,"Error",words.errorString());
    }


    QTextStream textStream(&words);
    textStream.flush();
    stringList.clear();


    while (true)
    {
           QString line = textStream.readLine();
        if (line.isNull())
            break;
        else
            stringList.append(line); // populate the stringlist
     }

    model->setStringList(stringList);

    updateBoard();


}


void Widget::on_rButton_clicked()
{
    QStringList temp;

    QString myQString = ui->letterLineEdit->text();
    QString oneLetter = myQString[0];

    for(QString q:stringList) {
        //if(q.contains(oneLetter),Qt::CaseInsensitive) {
        if(!q.contains(oneLetter)) {
            temp.append(q);
         }
    }
    stringList = temp;
    ui->numWordsRemainingLabel->setText("words remaining: " + QString::number(stringList.size()));
    updateBoard();
}



void Widget::on_displayRemWordsButton_clicked()
{
    ui->numWordsRemainingLabel->setText("words remaining: " + QString::number(stringList.size()));
    model->setStringList(stringList);

    ui->remainingWordsListView->setModel(model);
}




void Widget::on_kButton_clicked()
{
    QStringList temp;

    QString myQString = ui->letterLineEdit->text();
    QString oneLetter = myQString[0];

    for(QString q:stringList) {

        if(q.contains(oneLetter)) {
            temp.append(q);
        }
    }
    stringList = temp;
    ui->numWordsRemainingLabel->setText("words remaining: " + QString::number(stringList.size()));
    updateBoard();
}


void Widget::on_pButton_clicked()
{
    QStringList temp;

    QString myQString = ui->letterLineEdit->text();
    QString oneLetter = myQString[0];
    int placement = ui->placementSpinBox->value();

    for(QString q:stringList) {
        if(q[placement-1] == oneLetter) {
            temp.append(q);
        }
    }
    stringList = temp;
    ui->numWordsRemainingLabel->setText("words remaining: " + QString::number(stringList.size()));
    updateBoard();
}


void Widget::on_sButton_clicked()
{
    QStringList temp;

    QString myQString = ui->letterLineEdit->text();
    QString oneLetter = myQString[0];
    int placement = ui->placementSpinBox->value();

    for(QString q:stringList) {
        if(q[placement-1] != oneLetter) {
            temp.append(q);
        }
    }
    stringList = temp;
    ui->numWordsRemainingLabel->setText("words remaining: " + QString::number(stringList.size()));
    updateBoard();
}

void Widget::countLetters()
{
    mymap.clear();
    for(QString x:stringList) {
        for(QChar mychar:x) {
            if(mymap.count(mychar)) {
                mymap[mychar] += 1;
            } else {
                mymap[mychar] = 1;
            }
        }
    }
}

QString Widget::findBestWord()
{
    int biggestTotal = 0;
    QString retval = "a";
    for(QString q:stringList) {
        QString no_dups = "";
        int total = 0;
        for(QChar mychar:q) {
            if(!no_dups.contains(mychar)) {
                no_dups += mychar;
                total += mymap[mychar];
            }

        }
        if(total > biggestTotal) {
            retval = q;
            biggestTotal = total;
        }
    }
    return retval;
}

void Widget::updateBoard()
{
    ui->numWordsRemainingLabel->setText("words remaining: " + QString::number(stringList.size()));
    countLetters();
    QString mystring = findBestWord();
    ui->bestWordLabel->setText("best word: " + mystring);
}

