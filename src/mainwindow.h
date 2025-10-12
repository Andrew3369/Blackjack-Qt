#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <iostream>
#include <string>
#include <chrono>
//#include <thread>
//#include <random>
//#include <algorithm>
#include <cstdlib>
//#include <vector>
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
#include "uicontroller.h"
#include "gamecontroller.h"

#define g_ERROR -1

// constexpr int g_BLACKJACK = 21;
// constexpr int g_DEALER_STAND_THRESHOLD = 17;
//constexpr int g_card_xOffset = 125;


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
    Deck* p_Deck;
    Player* p_Player;
    Dealer* p_Dealer;
    QGraphicsScene* scene;

    UiController* uiCtrl;
    GameController* gameCtrl;
    GameState gameState;

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
    ~MainWindow();

// new methods after ui and game controller
protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    // ui displays
    void showPlayerHand();
    void showDealerHand(bool showTwoCards);

    // Main tablegame logic here
    inline void StartGame();
    void ResetGame();
    void GameConditions(bool playerStand = false);
    void ShowMenu();
    void UiInitializers();
    void resetUi();


    // onclick listeners
    void onStartClicked();
    void onExitClicked();
    void onHitClicked();
    void onDoubleDownClicked();
    void onStandClicked();
    void standLogic();
    void onResetClicked();

    void checkGameState(bool playerStand);
};

#endif // MAINWINDOW_H
