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

    UiInitializers();
    StartGame();
    MainGameLoop();
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
        //qDebug() << player->getHand()[i].displayCmd();
    }
    //qDebug() << player->getTotalValue();
    txt_playerHand = scene->addText("Player Hand: " + QString::number(player->getTotalValue()));
    txt_playerHand->setDefaultTextColor(Qt::white);
    txt_playerHand->setFont(QFont("Arial", 14));
    txt_playerHand->setPos(350, 525);
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

    //qDebug() << "Dealer Hand: " + QString::number(dealer->getTotalValue()); // this works?
    txt_dealerHand = scene->addText("Hand: " + QString::number(dealer->getFirstCardTotal()));
    txt_dealerHand->setDefaultTextColor(Qt::white);
    txt_dealerHand->setFont(QFont("Arial", 14));
    txt_dealerHand->setPos(350, 225);
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
    qDebug() << "Game Started...";
}

void MainWindow::ResetGame()
{
    player->removeCards();
    dealer->removeCards();
    resetUi();
    StartGame();
    qDebug() << "Game resetted...";
}

void MainWindow::MainGameLoop()
{
    showPlayerHand();
    showDealerHand();

    btn_Hit->setEnabled(true);
    btn_Stand->setEnabled(true);
}

void MainWindow::UiInitializers()
{
    qDebug() << "Initializing ui...";
    QPixmap backG(":/assets/other/tabletop.png");
    img_BckGrnd = scene->addPixmap(backG);
    img_BckGrnd->setZValue(-1); // push it behind all cards
    img_BckGrnd->setScale(2);

    btn_Hit = new QPushButton("Hit");
    btn_Stand = new QPushButton("Stand");
    btn_DblDown = new QPushButton("Double");
    btn_Reset = new QPushButton("Reset");
    scene->addWidget(btn_Hit)->setPos(50, 500);
    scene->addWidget(btn_Stand)->setPos(150, 500);
    scene->addWidget(btn_Reset)->setPos(150, 500);

    // hide buttons not needed yet
    btn_Reset->hide();
    btn_DblDown->hide();

    connect(btn_Hit, &QPushButton::clicked, this, &MainWindow::onHitClicked);
    connect(btn_Stand, &QPushButton::clicked, this, &MainWindow::onStandClicked);
    connect(btn_Reset, &QPushButton::clicked, this, &MainWindow::onResetClicked);
}

void MainWindow::resetUi()
{
    //scene->clear();
    qDebug() << "reset ui...";
}

void MainWindow::onHitClicked()
{
    qDebug() << "Dealer dealt card";
    player->addCard(deck->dealCard());
    showPlayerHand();

    if (player->getTotalValue() > g_BLACKJACK)
    {
        qDebug() << "Player busts";
        btn_Hit->hide();
        btn_Stand->hide();
        btn_Reset->show();
        // hide hit and stnad buttons, then display reset game
        //ResetGame();
    }
}

void MainWindow::onStandClicked()
{
    qDebug() << "PLayer stands! Dealer logic starts...";
    // dealer logic starts
}

void MainWindow::onResetClicked()
{
    resetUi();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete deck;
    delete player;
    delete dealer;
    delete scene;
}
