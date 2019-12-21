#ifndef MOVIE_H
#define MOVIE_H

#include "BalancedBinaryTree.h"
#include "HelpFunc.h"
#include <QWidget>
#include <QDebug>
#include <QLabel>
#include<sstream>

namespace Ui {
class Movie;
}

class Movie : public QWidget
{
    Q_OBJECT

public:
    explicit Movie(QWidget *parent = nullptr);
    ~Movie();
    void initUI();
    void initDict();
    void readKeyWord();
    void showDetail(QLabel* title);
    void showRecom(char* txtName);
    bool eventFilter(QObject * watched, QEvent * event);

private slots:
    void on_searchButton_clicked();

private:
    Ui::Movie *ui;
    BalancedBinaryTree* dict;
    CharStringLink* infoFileList;
    DocList* resultList;
};

#endif // MOVIE_H
