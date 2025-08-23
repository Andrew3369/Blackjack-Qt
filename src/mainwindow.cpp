#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QLabel *label = new QLabel(central);
    //QPixmap pix("C:/Users/andre/OneDrive/Desktop/Blackjack-Qt/Blackjack-Qt/assets/01_kerenel_Cards.png");
    QPixmap pix("./assets/01_kerenel_Cards.png");

    if (pix.isNull())
    {
        qDebug() << "failed loading image";

    }
    label->setPixmap(pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}
