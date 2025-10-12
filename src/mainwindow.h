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

// #include "deck.h"
// #include "player.h"
// #include "dealer.h"
#include "uicontroller.h"
#include "gamecontroller.h"

#define g_ERROR -1


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
    QGraphicsScene* scene;

    UiController* uiCtrl;
    GameController* gameCtrl;
    GameState gameState;

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

// new methods after ui and game controller
protected:
    void resizeEvent(QResizeEvent* event) override;

private:

    void checkGameState(bool playerStand);

    // onclick listeners
    void onStartClicked();
    void onExitClicked();
    void onHitClicked();
    void onDoubleDownClicked();
    void onStandClicked();
    void onResetClicked();
};

#endif // MAINWINDOW_H
