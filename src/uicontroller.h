#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPushButton>

//#include "mainwindow.h"

class uicontroller
{
private:
    QGraphicsScene* scene;

    // ui elements
    QGraphicsTextItem* txt_playerHand;
    QGraphicsTextItem* txt_dealerHand;
    QGraphicsTextItem* txt_winDeclare;

    // buttons
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
    uicontroller();
    ~uicontroller();
};

#endif // UICONTROLLER_H
