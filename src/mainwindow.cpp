#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    QGraphicsView *view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    //initializations
    uiCtrl = new UiController(scene);
    gameCtrl = new GameController();

    uiCtrl->setupMenuUi();

    connect(uiCtrl->getStartButton(), &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(uiCtrl->getExitButton(), &QPushButton::clicked, this, &MainWindow::onExitClicked);
}

void MainWindow::onStartClicked()
{
    uiCtrl->resetGameUi();
    uiCtrl->setupGameUi();
    //StartGame(); // put this into game controller
    gameCtrl->startGame();

    uiCtrl->showPlayerHand(gameCtrl->getPlayer()->getHand());
    uiCtrl->showDealerHand(gameCtrl->getDealer()->getHand(), false);

    // add check to see if anybody won?

    //connect(uiCtrl->getHitButton(), &QPushButton::clicked, this, &MainWindow::onHitClicked);
    connect(uiCtrl->getExitButton(), &QPushButton::clicked, this, &MainWindow::onExitClicked);
    connect(uiCtrl->getHitButton(), &QPushButton::clicked, this, &MainWindow::onHitClicked);
    connect(uiCtrl->getStandButton(), &QPushButton::clicked, this, &MainWindow::onStandClicked);
    connect(uiCtrl->getDblDownButton(), &QPushButton::clicked, this, &MainWindow::onDoubleDownClicked);
    connect(uiCtrl->getResetButton(), &QPushButton::clicked, this, &MainWindow::onResetClicked);
}

void MainWindow::onExitClicked()
{
    qDebug() << "Quitting application";
    QCoreApplication::quit();
}

void MainWindow::onHitClicked()
{
    qDebug() << "Dealer dealt card";

    gameCtrl->playerHit();
    uiCtrl->showPlayerHand(gameCtrl->getPlayer()->getHand());
    checkGameState(false);
}

void MainWindow::onDoubleDownClicked()
{
    qDebug() << "Player double downs";
    gameCtrl->playerHit();
    uiCtrl->showPlayerHand(gameCtrl->getPlayer()->getHand());
    checkGameState(false);
    //onStandClicked(); // might not need
}

void MainWindow::onStandClicked()
{
    uiCtrl->getHitButton()->hide();
    uiCtrl->getDblDownButton()->hide();
    uiCtrl->getStandButton()->hide();
    uiCtrl->showDealerHand(gameCtrl->getDealer()->getHand(), true);
    //gameCtrl->dealerHit();

    qDebug() << "Player stands! Dealer logic starts...";
    gameCtrl->playerStand(*uiCtrl);
    checkGameState(true);
    uiCtrl->getResetButton()->show();
}

void MainWindow::onResetClicked()
{
    qDebug() << "Resetting game";
    gameCtrl->resetGame();
    uiCtrl->resetGameUi();
    uiCtrl->getResetButton()->hide();
    uiCtrl->getStartButton()->show();
}

void MainWindow::checkGameState(bool playerStand)
{
    switch (gameCtrl->gameConditions(playerStand))
    {
        case GameState::PlayerWin:
            qDebug() << "Player has: " + QString::number(
                            gameCtrl->getPlayer()->getTotalValue())+ " , Player wins";
            uiCtrl->getHitButton()->hide();
            uiCtrl->getStandButton()->hide();
            uiCtrl->getDblDownButton()->hide();
            uiCtrl->getResetButton()->show();
            return;

        case GameState::DealerWin:
            qDebug() << "Dealer has: " + QString::number(
                            gameCtrl->getDealer()->getTotalValue()) + " , Dealer wins";
            uiCtrl->getHitButton()->hide();
            uiCtrl->getStandButton()->hide();
            uiCtrl->getDblDownButton()->hide();
            uiCtrl->getResetButton()->show();
            return;

        case GameState::PlayerBust:
            qDebug() << "Player busts, dealer wins";
            uiCtrl->getHitButton()->hide();
            uiCtrl->getStandButton()->hide();
            uiCtrl->getDblDownButton()->hide();
            uiCtrl->getResetButton()->show();
            return;

        case GameState::DealerBust:
            qDebug() << "Dealer busts, Player wins";
            uiCtrl->getHitButton()->hide();
            uiCtrl->getStandButton()->hide();
            uiCtrl->getDblDownButton()->hide();
            uiCtrl->getResetButton()->show();
            return;

        case GameState::Draw:
            qDebug() << "Push, Player and Dealer same count";
            uiCtrl->getHitButton()->hide();
            uiCtrl->getStandButton()->hide();
            uiCtrl->getDblDownButton()->hide();
            uiCtrl->getResetButton()->show();
            return;

        case GameState::NoState:
            uiCtrl->getHitButton()->hide();
            uiCtrl->getStandButton()->hide();
            uiCtrl->getDblDownButton()->hide();
            uiCtrl->getResetButton()->show();
            return;

        // i got no clue why i added error
        case GameState::Error:
            // uiCtrl->getHitButton()->hide();
            // uiCtrl->getStandButton()->hide();
            // uiCtrl->getDblDownButton()->hide();
            // uiCtrl->getResetButton()->show();
            qDebug() << "ERROR";
            return;
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    // resize window, makes everything scale with the window dimensions and what not
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gameCtrl;
    delete uiCtrl;
    delete scene;
    qDebug() << "Deleted memory allocations";
}
