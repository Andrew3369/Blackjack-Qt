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

    StartGame();

    // // background image
    QPixmap backG(":/assets/other/tabletop.png");
    QGraphicsPixmapItem* backGItem = scene->addPixmap(backG);
    backGItem->setZValue(-1); // push it behind all cards
    backGItem->setScale(2);
}

void MainWindow::showPlayerHand()
{
    //scene->clear();
    for (int i = 0; i < player->getHand().size(); i++)
    {
        int xOffset = g_card_xOffset * i;
        QString cardFilename = g_cardsFilePath + player->getHand()[i].toFilename();
        QPixmap cardPic(cardFilename);

        if (cardPic.isNull())
        {
            qDebug() << "Failed to load image from path: " + cardFilename;
            continue;
        }

        QGraphicsPixmapItem* cardItem = scene->addPixmap(cardPic);
        cardItem->setPos(250 + xOffset, 350);
        cardItem->setScale(2);
        qDebug() << player->getHand()[i].displayCmd();
    }
    qDebug() << player->getTotalValue();
    playerHandTxt = scene->addText("Player Hand: " + QString::number(player->getTotalValue()));
    playerHandTxt->setDefaultTextColor(Qt::white);
    playerHandTxt->setFont(QFont("Arial", 14));
    playerHandTxt->setPos(350, 525);
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
    cardItem1->setPos(250, 50);
    cardItem1->setScale(2);
    cardItem2->setPos(250 + g_card_xOffset, 50);
    cardItem2->setScale(2);

    qDebug() << "Dealer Hand: " + QString::number(dealer->getTotalValue()); // this works?
    // this doesnt :D
    dealerHandTxt = scene->addText("Hand: " + QString::number(dealer->getFirstCardTotal()));
    dealerHandTxt->setDefaultTextColor(Qt::white);
    dealerHandTxt->setFont(QFont("Arial", 14));
    dealerHandTxt->setPos(350, 225);
}

// TODO:
// rewrite instead of repeating dealers hand/full hand
void MainWindow::showDealerFullHand()
{
    //QGraphicsTextItem* textField = scene->addText(showDealerHand());
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

void MainWindow::StartGame()
{
    player->addCard(deck->dealCard());
    dealer->addCard(deck->dealCard());
    player->addCard(deck->dealCard());
    dealer->addCard(deck->dealCard());

    showPlayerHand();
    showDealerHand();
}

void MainWindow::ResetGame()
{
    player->removeCards();
    dealer->removeCards();
}

void MainWindow::UiInitializers()
{

}

MainWindow::~MainWindow()
{
    delete ui;
    delete deck;
    delete player;
    delete dealer;
    delete scene;
}
