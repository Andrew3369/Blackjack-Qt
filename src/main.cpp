#include "mainwindow.h"
#include "deck.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Deck deck;
    deck.displayDeck();
    w.show();

    return a.exec();
}
