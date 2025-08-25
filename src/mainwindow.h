#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <iostream>
//#include <chrono>
//#include <thread>
//#include <random>
//#include <algorithm>
#include <cstdlib>
//#include <vector>
#include "dealer.h"
#include <QPixmap>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <qgraphicsitem.h>
#include <QPropertyAnimation>

#include "deck.h"
#include "player.h"
#include "dealer.h"

#define g_ERROR -1

constexpr int g_BLACKJACK = 21;
constexpr int g_DEALER_STAND_THRESHOLD = 17;
constexpr int g_card_xOffset = 125;


typedef struct
{

} hand_Pos;

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

public:
    MainWindow(QWidget *parent = nullptr);
    void showPlayerHand();
    void showDealerHand();
    void showDealerFullHand();
    ~MainWindow();

    //Main tablegame logic here
};
#endif // MAINWINDOW_H
