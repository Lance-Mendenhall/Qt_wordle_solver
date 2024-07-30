#ifndef WIDGET_H
#define WIDGET_H
#include <QFile>
#include <QStringListModel>
#include <QMap>

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    QStringList stringList;
    ~Widget();

private slots:
    void on_startButton_clicked();
    void on_rButton_clicked();
    void on_displayRemWordsButton_clicked();
    void on_kButton_clicked();
    void on_pButton_clicked();
    void on_sButton_clicked();
    void countLetters();
    QString findBestWord();
    void updateBoard();

private:
    Ui::Widget *ui;
    QFile words;
    QStringListModel * model;
    QMap<QChar,int> mymap;
};
#endif // WIDGET_H
