#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    QGraphicsView *view = new QGraphicsView(scene, this);
    //QLabel* cardItem = new QLabel(this);
    setCentralWidget(view);
    //initializations
    deck = new Deck();
    player = new Player();
    dealer = new Dealer();

    player->addCard(deck->dealCard());
    dealer->addCard(deck->dealCard());
    player->addCard(deck->dealCard());
    dealer->addCard(deck->dealCard());

    showPlayerHand();
    // showDealerFullHand();
    showDealerHand();


    // testing (deal card
    //deck->displayDeck();
    //std::vector<Card> hand;
    //hand.push_back(deck->dealCard());
    //hand.push_back(deck->dealCard());

    // // background image
    QPixmap backG(":/assets/other/tabletop.png");
    QGraphicsPixmapItem* backGItem = scene->addPixmap(backG);
    backGItem->setZValue(-1); // push it behind all cards
    backGItem->setScale(2);



    //filenames
    // QString cardFilename1 = g_cardsFilePath + player->getHand()[0].toFilename();
    // QString cardFilename2 = g_cardsFilePath + player->getHand()[1].toFilename();

    // // actual cards
    // QPixmap card1(cardFilename1);
    // QGraphicsPixmapItem* cardItem1 = scene->addPixmap(card1);
    // QPixmap card2(cardFilename2);
    // QGraphicsPixmapItem* cardItem2 = scene->addPixmap(card2);
    // if (card1.isNull() && card2.isNull())
    //     qDebug() << "failed loading image: " + cardFilename1 + " and " + cardFilename2;

    // cardItem1->setPos(250, 0);
    // cardItem1->setScale(2);
    // cardItem2->setPos(375, 0);
    // cardItem2->setScale(2);


    // for (int i = 0; i < player->getHand().size(); i++)
    // {
    //     int xOffset = 125 * i;
    //     QString cardFilename = g_cardsFilePath + player->getHand()[i].toFilename();
    //     QPixmap cardPic(cardFilename);

    //     if (cardPic.isNull())
    //     {
    //         qDebug() << "Failed to load image from path: " + cardFilename;
    //         continue;
    //     }

    //     QGraphicsPixmapItem* cardItem = scene->addPixmap(cardPic);
    //     cardItem->setPos(250 + xOffset, 0);
    //     cardItem->setScale(2);
    // }

}


void MainWindow::showPlayerHand()
{
    scene->clear();
    // ui and anims go here
    for (int i = 0; i < player->getHand().size(); i++)
    {
        int xOffset = 125 * i;
        QString cardFilename = g_cardsFilePath + player->getHand()[i].toFilename();
        QPixmap cardPic(cardFilename);

        if (cardPic.isNull())
        {
            qDebug() << "Failed to load image from path: " + cardFilename;
            continue;
        }

        QGraphicsPixmapItem* cardItem = scene->addPixmap(cardPic);
        cardItem->setPos(250 + xOffset, 250);
        cardItem->setScale(2);
        qDebug() << player->getHand()[i].displayCmd();
    }
}


// TODO:
// rewrite instead of repeting
void MainWindow::showDealerFullHand()
{
    for (int i = 0; i < dealer->getHand().size(); i++)
    {
        int xOffset = g_card_xOffset * i;
        QString cardFilename = g_cardsFilePath + dealer->getHand()[i].toFilename();
        QPixmap cardPic(cardFilename);

        if (cardPic.isNull())
        {
            qDebug() << "Failed to load image from path: " + cardFilename;
            continue;
        }

        QGraphicsPixmapItem* cardItem = scene->addPixmap(cardPic);
        cardItem->setPos(250 + xOffset, 0);
        cardItem->setScale(2);
    }
}

void MainWindow::showDealerHand()
{
    QString cardFilename1 = g_cardsFilePath + dealer->getHand()[0].toFilename();
    QPixmap cardPic1(cardFilename1);
    if (cardPic1.isNull())
        qDebug() << "Failed to load image from path: " + cardFilename1;

    QString cardFilename2 = ":/assets/cards/backside_red.png";
    QPixmap cardPic2(cardFilename2);
    if (cardPic2.isNull())
        qDebug() << "Failed to load image from path: " + cardFilename2;

    QGraphicsPixmapItem* cardItem1 = scene->addPixmap(cardPic1);
    QGraphicsPixmapItem* cardItem2 = scene->addPixmap(cardPic2);
    cardItem1->setPos(250, 0);
    cardItem1->setScale(2);
    cardItem2->setPos(250 + g_card_xOffset, 0);
    cardItem2->setScale(2);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete deck;
    delete player;
    delete dealer;
    delete scene;
}
