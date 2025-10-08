#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include "card.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include <QPushButton>
#include <QDebug>
#include <QGraphicsProxyWidget>
#include <qgraphicsitem.h>


//#include "mainwindow.h"

class UiController
{
private:
    QGraphicsScene* scene;

    // ui elements
    QGraphicsTextItem* txt_playerHand;
    QGraphicsTextItem* txt_dealerHand;
    QGraphicsTextItem* txt_winDeclare;
    QGraphicsPixmapItem* img_BckGrnd;
    QGraphicsPixmapItem* img_Title;

    // buttons
    QPushButton* btn_Start;
    QPushButton* btn_Exit;
    QPushButton* btn_Hit;
    QPushButton* btn_DblDown;
    QPushButton* btn_Stand;
    QPushButton* btn_Reset;

    // ui groups
    QGraphicsItemGroup* group_playerUi;
    QGraphicsItemGroup* group_dealerUi;
    //QGraphicsItemGroup* group_genericUi;

public:
    UiController(QGraphicsScene* scene);
    ~UiController() {}

    // change these names
    void setupMenu();
    void setupGame();
    void resetGame();

    void showPlayerHand(const std::vector<Card>& hand);
    void showDealerHand(const std::vector<Card>& hand, bool revealAll);

    QPushButton* getStartButton() const { return btn_Start; }
    QPushButton* getExitButton() const { return btn_Exit; }
    QPushButton* getHitButton() const { return btn_Hit; }
    QPushButton* getStandButton() const { return btn_Stand; }
    QPushButton* getDblDownButton() const { return btn_DblDown; }
    QPushButton* getResetButton() const { return btn_Reset; }

};

#endif // UICONTROLLER_H
