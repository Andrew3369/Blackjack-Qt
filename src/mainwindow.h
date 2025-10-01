#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <iostream>
#include <string>
#include <chrono>
#include <thread>
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
    Ui::MainWindow* ui;

    // essential objects
    Deck* deck;
    Player* player;
    Dealer* dealer;
    QGraphicsScene* scene;

    // ui elements
    QGraphicsTextItem* txt_playerHand;
    QGraphicsTextItem* txt_dealerHand;
    QGraphicsTextItem* txt_winDeclare;
    QPushButton* btn_Start;
    QPushButton* btn_Exit;
    QPushButton* btn_Hit;
    QPushButton* btn_DblDown;
    QPushButton* btn_Stand;
    QPushButton* btn_Reset;
    QGraphicsPixmapItem* img_BckGrnd;
    QGraphicsPixmapItem* img_Title;

    // ui groups
    QGraphicsItemGroup* group_playerUi;
    QGraphicsItemGroup* group_dealerUi;
    QGraphicsItemGroup* group_genericUi;

public:
    MainWindow(QWidget* parent = nullptr);

    // ui displays
    void showPlayerHand();
    void showDealerHand(bool showTwoCards);
    void showDealerFullHand();

    // Main tablegame logic here
    void StartGame();
    void ResetGame();
    void GameConditions(bool playerStand = false);
    void ShowMenu();
    void UiInitializers();
    void resetUi();

    // onclick listeners
    void onStartClicked();
    void onExitClicked();
    void onHitClicked();
    void onStandClicked();
    void onResetClicked();

    ~MainWindow();
};
#endif // MAINWINDOW_H
