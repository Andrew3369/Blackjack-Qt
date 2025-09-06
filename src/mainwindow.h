#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <iostream>
#include <string>
//#include <chrono>
//#include <thread>
//#include <random>
//#include <algorithm>
#include <cstdlib>
//#include <vector>
#include "dealer.h"
#include <QPixmap>
#include <QLabel>
#include <qgraphicsitem.h>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "deck.h"
#include "player.h"
#include "dealer.h"

#define g_ERROR -1

constexpr int g_BLACKJACK = 21;
constexpr int g_DEALER_STAND_THRESHOLD = 17;
constexpr int g_card_xOffset = 125;


QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    Deck* deck;
    Player* player;
    Dealer* dealer;
    QGraphicsScene* scene;

    // change these
    QGraphicsTextItem* txt_playerHand;
    QGraphicsTextItem* txt_dealerHand;
    QPushButton* btn_Hit;
    QPushButton* btn_DblDown;
    QPushButton* btn_Stand;
    QGraphicsPixmapItem* img_BckGrnd;

public:
    MainWindow(QWidget *parent = nullptr);

    //Main tablegame logic here
    void showPlayerHand();
    void showDealerHand();
    void showDealerFullHand();

    void StartGame();
    void ResetGame();
    void MainGameLoop();
    void GameConditions();
    void UiInitializers();
    void resetUi();

    void onHitClicked();
    void onStandClicked();

    ~MainWindow();
};
#endif // MAINWINDOW_H
