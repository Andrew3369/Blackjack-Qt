#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    // testing (deal card)
    Deck deck;
    deck.displayDeck();
    std::vector<Card> hand;
    hand.push_back(deck.dealCard());
    hand.push_back(deck.dealCard());


    ui->setupUi(this);
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QLabel *label = new QLabel(central);

    QString cardFilename = ":/assets/" + hand[0].toFilename();

    QPixmap pix(cardFilename);
    if (pix.isNull())
        qDebug() << "failed loading image: " + cardFilename;

    label->setPixmap(pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}
