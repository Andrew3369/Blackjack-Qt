#include "uicontroller.h"

UiController::UiController(QGraphicsScene* scene)
{
    this->scene = scene; // or else crashes
    txt_playerHand = nullptr;
    txt_dealerHand = nullptr;
    txt_winDeclare = nullptr;
    group_playerUi = scene->createItemGroup({});
    group_dealerUi = scene->createItemGroup({});
}

void UiController::setupMenu()
{
    img_Title = scene->addPixmap(QPixmap(":/assets/other/logo.png"));
    img_Title->setScale(0.5);
    img_Title->setZValue(-1);

    btn_Start = new QPushButton("Start");
    btn_Exit = new QPushButton("Quit");
    scene->addWidget(btn_Start)->setPos(50, 500);
    scene->addWidget(btn_Exit)->setPos(150, 500);

    qApp->setStyleSheet(
        "QPushButton {"
        "  background-color: #2b2b2b;"
        "  color: white;"
        "  border: 2px solid #4caf50;"
        "  border-radius: 8px;"
        "  padding: 6px 12px;"
        "  font-size: 14px;"
        "}"
        "QPushButton:hover { background-color: #4caf50; }"
        "QPushButton:pressed { background-color: #388e3c; }"
        );
}

void UiController::setupGame()
{
    qDebug() << "Initializing ui...";
    img_BckGrnd = scene->addPixmap(QPixmap((":/assets/other/tabletop.png")));
    img_BckGrnd->setZValue(-1);
    img_BckGrnd->setScale(2);

    // add soon
    //group_genericUi->addToGroup(img_BckGrnd);

    btn_Start->hide();
    btn_Exit->hide();

    // buttons
    btn_Hit = new QPushButton("Hit");
    btn_Stand = new QPushButton("Stand");
    btn_DblDown = new QPushButton("Double");
    btn_Reset = new QPushButton("Reset");

    scene->addWidget(btn_Hit)->setPos(50, 500);
    scene->addWidget(btn_Stand)->setPos(150, 500);
    scene->addWidget(btn_DblDown)->setPos(100, 470);
    scene->addWidget(btn_Reset)->setPos(150, 500);
    btn_Reset->hide();
    //btn_DblDown->hide();

    txt_playerHand = scene->addText("");
    txt_playerHand->setDefaultTextColor(Qt::white);
    txt_playerHand->setFont(QFont("Arial", 14));
    txt_playerHand->setPos(350, 525);

    txt_dealerHand = scene->addText("");
    txt_dealerHand->setDefaultTextColor(Qt::white);
    txt_dealerHand->setFont(QFont("Arial", 14));
    txt_dealerHand->setPos(350, 225);
}

void UiController::resetGame()
{
    QList<QGraphicsItem*> itemsPlayer = group_playerUi->childItems();
    QList<QGraphicsItem*> itemsDealer = group_dealerUi->childItems();

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

    // this probaly wont work i was cooking
    // for (QGraphicsItem* item : itemsPlayer, itemsDealer)
    // {
    //     group_playerUi->removeFromGroup(item);
    //     group_dealerUi->removeFromGroup(item);
    //     scene->removeItem(item);
    //     delete item;
    // }
}

void UiController::showPlayerHand(const std::vector<Card>& hand)
{
    uint8_t i, cardTotal = 0;
    for (const auto& card : hand)
    {
        QString filename = g_cardsFilePath + card.toFilename();
        QPixmap cardImg(filename);
        auto* item = scene->addPixmap(cardImg);
        item->setPos(250 + g_card_xOffset * i++, 350);
        item->setScale(2);
        group_playerUi->addToGroup(item);
        cardTotal += card.getValue();
    }
    txt_playerHand->setPlainText(
        "Player Hand: " + QString::number(cardTotal));
}

void UiController::showDealerHand(const std::vector<Card>& hand, bool revealAll)
{
    if (revealAll)
    {
        uint8_t i, cardTotal = 0;
        for (const auto& card : hand)
        {
            QString filename = g_cardsFilePath + card.toFilename();
            QPixmap cardImg(filename);
            auto* item = scene->addPixmap(cardImg);
            item->setPos(250 + g_card_xOffset * i++, 50);
            item->setScale(2);
            group_dealerUi->addToGroup(item);
            cardTotal += card.getValue();
        }
        txt_dealerHand->setPlainText(
            "Hand: " + QString::number(cardTotal));
    }
    else
    {
        QString cardFilename1 = g_cardsFilePath + hand[0].toFilename();
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
        group_dealerUi->addToGroup(txt_dealerHand);
        txt_dealerHand->setPlainText(
            "Hand: " + QString::number(hand[0].getValue()));
    }
}
