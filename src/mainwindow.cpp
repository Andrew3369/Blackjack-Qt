#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <qgraphicsitem.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //initializations
    deck = new Deck();
    //player = new Player();
    //dealer = new Dealer();

    // testing (deal card
    deck->displayDeck();
    std::vector<Card> hand;
    hand.push_back(deck->dealCard());
    hand.push_back(deck->dealCard());


    ui->setupUi(this);
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QLabel *label = new QLabel(central);
    QGraphicsScene *scene = new QGraphicsScene(this);
    QGraphicsView *view = new QGraphicsView(scene, this);

    QString cardFilename1 = ":/assets/" + hand[0].toFilename();
    QString cardFilename2 = ":/assets/" + hand[1].toFilename();

    QPixmap card1(cardFilename1);
    QGraphicsPixmapItem* cardItem1 = scene->addPixmap(card1);

    QPixmap card2(cardFilename2);
    QGraphicsPixmapItem* cardItem2 = scene->addPixmap(card2);

    if (card1.isNull() && card2.isNull())
        qDebug() << "failed loading image: " + cardFilename1 + " and " + cardFilename2;

    cardItem1->setPos(100, 500);
    cardItem2->setPos(400, 500);

    //view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete deck;
}
