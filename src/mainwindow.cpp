#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    QGraphicsView *view = new QGraphicsView(scene, this);
    //QLabel* cardItem = new QLabel(this);
    setCentralWidget(view);
    uiCtrl = new UiController(scene);
    gameCtrl = new GameController();

    //initializations
    p_Deck = new Deck();
    p_Player = new Player();
    p_Dealer = new Dealer();

    group_playerUi = scene->createItemGroup({});
    group_dealerUi = scene->createItemGroup({});

    //group_dealerUi = new QGraphicsItemGroup();
    //group_genericUi = new QGraphicsItemGroup();

    // text elements
    txt_playerHand = nullptr;
    txt_dealerHand = nullptr;
    txt_winDeclare = nullptr;

    uiCtrl->setupMenu();

    connect(uiCtrl->getStartButton(), &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(uiCtrl->getExitButton(), &QPushButton::clicked, this, &MainWindow::onExitClicked);
    connect(uiCtrl->getHitButton(), &QPushButton::clicked, this, &MainWindow::onHitClicked);
    connect(uiCtrl->getStandButton(), &QPushButton::clicked, this, &MainWindow::onStandClicked);
    connect(uiCtrl->getDblDownButton(), &QPushButton::clicked, this, &MainWindow::onDoubleDownClicked);

    //ShowMenu();
}

void MainWindow::ShowMenu()
{
    img_Title = new QGraphicsPixmapItem();
    QPixmap backG(":/assets/other/logo.png");
    if (backG.isNull())
        qDebug() << "not loaded?";

    // add to group ui eventually?
    img_Title = scene->addPixmap(backG);
    img_Title->setZValue(-1); // push it behind all cards
    img_Title->setScale(0.5);

    // btn_Start = new QPushButton("Start");
    // btn_Exit = new QPushButton("Quit");
    // scene->addWidget(btn_Start)->setPos(50, 500);
    // scene->addWidget(btn_Exit)->setPos(150, 500);
    /*connect(btn_Start, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(btn_Exit, &QPushButton::clicked, this, &MainWindow::onExitClicked);
*/

    connect(uiCtrl->getStartButton(), &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(uiCtrl->getExitButton(), &QPushButton::clicked, this, &MainWindow::onExitClicked);

}

void MainWindow::showPlayerHand()
{
    for (uint8_t i = 0; i < p_Player->getHand().size(); i++)
    {
        int xOffset = g_card_xOffset * i;
        QString cardFilename = g_cardsFilePath + p_Player->getHand()[i].toFilename();
        QPixmap cardPic(cardFilename);

        if (cardPic.isNull())
        {
            qDebug() << "Failed to load image from path: " + cardFilename;
            continue;
        }

        QGraphicsPixmapItem* cardItem = scene->addPixmap(cardPic);
        cardItem->setPos(250 + xOffset, 350);
        cardItem->setScale(2);

        // testing groups
        group_playerUi->addToGroup(cardItem);

        //qDebug() << player->getHand()[i].displayCmd();
    }

    // display player hand total
    group_playerUi->addToGroup(txt_playerHand);
    txt_playerHand->setPlainText(
        "Player Hand: " + QString::number(p_Player->getTotalValue()));
}

void MainWindow::showDealerHand(bool showTwoCards)
{
    if (!showTwoCards)
    {
        QString cardFilename1 = g_cardsFilePath + p_Dealer->getHand()[0].toFilename();
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

        group_dealerUi->addToGroup(cardItem1);
        group_dealerUi->addToGroup(cardItem2);
        //qDebug() << "Dealer Hand: " + QString::number(dealer->getTotalValue()); // this works?
        group_dealerUi->addToGroup(txt_dealerHand);
        txt_dealerHand->setPlainText(
            "Hand: " + QString::number(p_Dealer->getFirstCardTotal()));
    }
    else
    {
        for (uint8_t i = 0; i < p_Dealer->getHand().size(); i++)
        {
            int xOffset = g_card_xOffset * i;
            QString cardFilename = g_cardsFilePath + p_Dealer->getHand()[i].toFilename();
            QPixmap cardPic(cardFilename);

            if (cardPic.isNull())
                qDebug() << "Failed to load image from path: " + cardFilename;

            QGraphicsPixmapItem *cardItem = scene->addPixmap(cardPic);
            group_dealerUi->addToGroup(cardItem);
            cardItem->setPos(250 + xOffset, 50);
            cardItem->setScale(2);
        }

        // display text
        group_dealerUi->addToGroup(txt_dealerHand);
        txt_dealerHand->setPlainText(
            "Hand: " + QString::number(p_Dealer->getTotalValue()));
    }
}

void MainWindow::StartGame()
{
    p_Player->addCard(p_Deck->dealCard());
    p_Dealer->addCard(p_Deck->dealCard());
    p_Player->addCard(p_Deck->dealCard());
    p_Dealer->addCard(p_Deck->dealCard());

    //GameConditions();

    qDebug() << "Game Started...";
}

void MainWindow::ResetGame()
{
    p_Player->removeCards();
    qDebug() << "Player cards removed...";
    p_Dealer->removeCards();
    qDebug() << "Dealer cards removed...";
    resetUi();
    StartGame();
    qDebug() << "Game resetted...";
}

void MainWindow::GameConditions(bool playerStand)
{
    // game conditions after the player stands
    if (playerStand)
    {
        if (p_Dealer->getTotalValue() == p_Player->getTotalValue())
        {
            qDebug() << "Push! No winner";
            btn_Hit->hide();
            btn_DblDown->hide();
            btn_Stand->hide();
            btn_Reset->show();
        }
        else if (p_Dealer->getTotalValue() == g_BLACKJACK)
        {
            qDebug() << "Dealer has Blackjack!";
            btn_Hit->hide();
            btn_DblDown->hide();
            btn_Stand->hide();
            btn_Reset->show();
        }
        else if (p_Dealer->getTotalValue() > g_BLACKJACK)
        {
            qDebug() << "Dealer busts! Player wins";
            btn_Hit->hide();
            btn_DblDown->hide();
            btn_Stand->hide();
            btn_Reset->show();
        }
        // can probably combine these 2 later
        else if (p_Dealer->getTotalValue() > p_Player->getTotalValue())
        {
            qDebug() << "Dealer has higher count! Dealer wins";
            btn_Hit->hide();
            btn_DblDown->hide();
            btn_Stand->hide();
            btn_Reset->show();
        }
        else if (p_Player->getTotalValue() > p_Dealer->getTotalValue())
        {
            qDebug() << "Player wins!";
            btn_Hit->hide();
            btn_Stand->hide();
            btn_Reset->show();
        }
    }
    else
    {
        if (p_Player->getTotalValue() > g_BLACKJACK)
        {
            qDebug() << "Player busts, Dealer wins";
            btn_Hit->hide();
            btn_DblDown->hide();
            btn_Stand->hide();
            btn_Reset->show();
        }
        else if (p_Player->getTotalValue() == g_BLACKJACK)
        {
            onStandClicked();
        }
    }
}

void MainWindow::UiInitializers()
{
    qDebug() << "Initializing ui...";

    QPixmap backG(":/assets/other/tabletop.png");
    if (backG.isNull())
        qDebug() << "not l;oaded?";
    //group_genericUi->addToGroup(img_BckGrnd);
    img_BckGrnd = scene->addPixmap(backG);
    img_BckGrnd->setZValue(-1); // push it behind all cards
    img_BckGrnd->setScale(2);
    //group_genericUi->addToGroup(img_BckGrnd);

    // buttons
    btn_Hit = new QPushButton("Hit");
    btn_Stand = new QPushButton("Stand");
    btn_DblDown = new QPushButton("Double");
    btn_Reset = new QPushButton("Reset");
    scene->addWidget(btn_Hit)->setPos(50, 500);
    scene->addWidget(btn_Stand)->setPos(150, 500);
    scene->addWidget(btn_DblDown)->setPos(100, 470);
    scene->addWidget(btn_Reset)->setPos(150, 500);
    // hide buttons not needed yet
    btn_Reset->hide();
    //btn_DblDown->hide();

    /* INITIALIZE ALL UI BEFORE CHANGING THEM*/
    txt_playerHand = scene->addText(""); // display nothing
    txt_playerHand->setDefaultTextColor(Qt::white);
    txt_playerHand->setFont(QFont("Arial", 14));
    txt_playerHand->setPos(350, 525);

    txt_dealerHand = scene->addText("");
    txt_dealerHand->setDefaultTextColor(Qt::white);
    txt_dealerHand->setFont(QFont("Arial", 14));
    txt_dealerHand->setPos(350, 225);

    // connect onClick() listeners
    connect(btn_Hit, &QPushButton::clicked, this, &MainWindow::onHitClicked);
    connect(btn_DblDown, &QPushButton::clicked, this, &MainWindow::onDoubleDownClicked);
    connect(btn_Stand, &QPushButton::clicked, this, &MainWindow::onStandClicked);
    connect(btn_Reset, &QPushButton::clicked, this, &MainWindow::onResetClicked);
}

void MainWindow::resetUi()
{
    qDebug() << "Reset ui...";

    // player ui removal
    if (group_playerUi && group_dealerUi)
    {
        QList<QGraphicsItem*> itemsPlayer = group_playerUi->childItems();
        QList<QGraphicsItem*> itemsDealer = group_dealerUi->childItems();

        // theres gotta be an easier way instead of 2 loops, maybe merge into 1 var only
        for (QGraphicsItem* item : itemsPlayer)
        { // player
            group_playerUi->removeFromGroup(item);
            scene->removeItem(item);
            delete item;
        }
        for (QGraphicsItem* item : itemsDealer)
        { // dealer
            group_playerUi->removeFromGroup(item);
            scene->removeItem(item);
            delete item;
        }
    }
    btn_Reset->hide();
    btn_Start->show();
}

void MainWindow::onStartClicked()
{
    uiCtrl->resetGame();
    uiCtrl->setupGame();
    //StartGame(); // put this into game controller
    gameCtrl->StartGame();

    uiCtrl->showPlayerHand(gameCtrl->getPlayer()->getHand());
    uiCtrl->showDealerHand(gameCtrl->getDealer()->getHand(), false);

    //connect(uiCtrl->getHitButton(), &QPushButton::clicked, this, &MainWindow::onHitClicked);
    connect(uiCtrl->getExitButton(), &QPushButton::clicked, this, &MainWindow::onExitClicked);
    connect(uiCtrl->getHitButton(), &QPushButton::clicked, this, &MainWindow::onHitClicked);
    connect(uiCtrl->getStandButton(), &QPushButton::clicked, this, &MainWindow::onStandClicked);
    connect(uiCtrl->getDblDownButton(), &QPushButton::clicked, this, &MainWindow::onDoubleDownClicked);

    // btn_Start->hide();
    // btn_Exit->hide();
    // UiInitializers();
    // StartGame();
    // showPlayerHand();
    // showDealerHand(false);
    // GameConditions(false);
}

void MainWindow::onExitClicked()
{
    qDebug() << "Quitting application";
    QCoreApplication::quit();
}

void MainWindow::onHitClicked()
{
    qDebug() << "Dealer dealt card";
    // gameCtrl->PlayerHit();
    // uiCtrl->showPlayerHand(gameCtrl->getPlayer()->getHand());
    // p_Player->addCard(p_Deck->dealCard());
    // showPlayerHand();
    // GameConditions(false);
}

void MainWindow::onDoubleDownClicked()
{
    qDebug() << "Player double downs";
    // btn_DblDown->hide();
    // p_Player->toggleDoubledDown();
    // std::cout << p_Player->doubleDown();

    // p_Player->addCard(p_Deck->dealCard());
    // showPlayerHand();
    // GameConditions(false);

    // //std::this_thread::sleep_for(std::chrono::seconds(1));
    // showDealerHand(true);
    // standLogic();
    // GameConditions(true);
}

void MainWindow::onStandClicked()
{
    qDebug() << "Player stands! Dealer logic starts...";
    btn_Hit->hide();
    btn_DblDown->hide();
    btn_Stand->hide();
    showDealerHand(true);
    standLogic();
    GameConditions(true);
}

void MainWindow::standLogic()
{
    while (p_Dealer->getTotalValue() < g_DEALER_STAND_THRESHOLD)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        p_Dealer->addCard(p_Deck->dealCard());
        showDealerHand(true);
    }
}

void MainWindow::onResetClicked()
{
    ResetGame();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete p_Deck;
    delete p_Player;
    delete p_Dealer;
    delete scene;
    qDebug() << "Deleted memory allocations";
}
